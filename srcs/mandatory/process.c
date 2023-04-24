/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:56:23 by hleung            #+#    #+#             */
/*   Updated: 2023/04/21 15:48:40 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

// static void	close_pipes(int	fd[2])
// {
// 	close(fd[0]);
// 	close(fd[1]);
// }

// static int	*get_fd(void)
// {
// 	int	*fd;

// 	fd = (int *)malloc(sizeof(int) * 2);
// 	if (!fd)
// 	{
// 		perror("Malloc error");
// 		return (NULL);
// 	}
// 	if (pipe(fd) == -1)
// 	{
// 		perror("Error opening pipe");
// 		return (NULL);
// 	}
// 	return (fd);
// }

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
	}
	if (dup2(pipex->infile, STDIN_FILENO) == -1)
		free_pipex_exit(pipex);
	close(pipex->infile);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		free_pipex_exit(pipex);
	close(fd[1]);
	if (!pipex->cmd1)
		exit(EXIT_FAILURE);
	execve(pipex->cmd1, pipex->cmd1_strs, envp);
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
	if (!pipex->cmd2)
		exit(EXIT_FAILURE);
	execve(pipex->cmd2, pipex->cmd2_strs, envp);
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
	close(fd[0]);
	close(fd[1]);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	wait_status(pipex, 1);
	wait_status(pipex, 2);
}
