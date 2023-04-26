/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:56:23 by hleung            #+#    #+#             */
/*   Updated: 2023/04/26 17:22:29 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	close_pipes(int	fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

static void	first_child(t_pipex *pipex, int fd[2], char **envp)
{
	close(fd[0]);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->infile == -1)
	{
		close(fd[1]);
		if (pipex->outfile != -1)
			close(pipex->outfile);
		free_pipex_exit(pipex);
	}
	if (dup2(pipex->infile, STDIN_FILENO) == -1)
		free_pipex_exit(pipex);
	close(pipex->infile);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		free_pipex_exit(pipex);
	close(fd[1]);
	if (pipex->cmd1)
		execve(pipex->cmd1, pipex->cmd1_strs, envp);
	close(0);
	close(1);
	close_pipes(fd);
	free_pipex_exit(pipex);
}

static void	second_child(t_pipex *pipex, int fd[2], char **envp)
{
	close(fd[1]);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		free_pipex_exit(pipex);
	close(fd[0]);
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
		free_pipex_exit(pipex);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->cmd2)
		execve(pipex->cmd2, pipex->cmd2_strs, envp);
	close(0);
	close(1);
	close_pipes(fd);
	free_pipex_exit(pipex);
}

void	launch_processes(t_pipex *pipex, char **envp)
{
	int	fd[2];

	if (pipe(fd) == -1)
		free_pipex_exit(pipex);
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		free_pipex_exit(pipex);
	if (pipex->pid1 == 0)
		first_child(pipex, fd, envp);
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
		free_pipex_exit(pipex);
	if (pipex->pid2 == 0)
		second_child(pipex, fd, envp);
	close_pipes(fd);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	wait_status(pipex, 2);
	close(STDIN_FILENO);
	wait_status(pipex, 1);
}
