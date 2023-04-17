/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:56:23 by hleung            #+#    #+#             */
/*   Updated: 2023/04/17 14:02:50 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	close_pipes(int	*fd)
{
	close(fd[0]);
	close(fd[1]);
}

static int	*get_fd(void)
{
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 2);
	if (!fd)
	{
		perror("Malloc error");
		return (NULL);
	}
	if (pipe(fd) == -1)
	{
		perror("Error opening pipe");
		return (NULL);
	}
	return (fd);
}

static void	first_child(t_pipex *pipex, char **envp)
{
	close(pipex->fd[0]);
	if (dup2(pipex->infile, STDIN_FILENO) == -1)
	{
		free_pipex(pipex);
		strerror_exit();
	}
	if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
	{
		free_pipex(pipex);
		strerror_exit();
	}
	if (!pipex->cmd1)
		exit(0);
	execve(pipex->cmd1, pipex->cmd1_strs, envp);
}

static void	second_child(t_pipex *pipex, char **envp)
{
	close(pipex->fd[1]);
	if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
	{
		free_pipex(pipex);
		strerror_exit();
	}
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
	{
		free_pipex(pipex);
		strerror_exit();
	}
	if (!pipex->cmd2)
		exit(0);
	execve(pipex->cmd2, pipex->cmd2_strs, envp);
}

void	launch_processes(t_pipex *pipex, char **envp)
{
	pipex->fd = get_fd();
	if (!pipex->fd)
		free_pipex(pipex);
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
	{
		perror("Error forking process");
		free_pipex(pipex);
	}
	if (pipex->pid1 == 0)
		first_child(pipex, envp);
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
	{
		perror("Error forking process");
		free_pipex(pipex);
	}
	if (pipex->pid2 == 0)
		second_child(pipex, envp);
	close_pipes(pipex->fd);
	wait_status(pipex, 1);
	wait_status(pipex, 2);
}
