/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:18:09 by hleung            #+#    #+#             */
/*   Updated: 2023/04/18 12:22:26 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_b.h"

static void	close_pipes(int	*fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	*get_fd(void)
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

int	*get_pids(int cmd_count)
{
	int	*pids;

	pids = (int *)malloc(sizeof(int) * cmd_count);
	if (!pids)
	{
		perror("Malloc error");
		return (NULL);
	}
	return (pids);
}

void	dup2s(t_pipex_b *pipex, int rd, int wr)
{
	if (dup2(rd, STDIN_FILENO) == -1)
		free_pipex_exit(pipex);
	close(pipex->fd[0]);
	if (dup2(wr, STDOUT_FILENO) == -1)
		free_pipex_exit(pipex);
}

void	child_processes(t_pipex_b *pipex, char **envp, int idx)
{
	t_cmds	*cmd;

	if (idx == 0)
		dup2s(pipex, pipex->infile, pipex->fd[1]);
	else if (idx == pipex->cmd_count - 1)
	{
		close(pipex->fd[1]);
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			free_pipex_exit(pipex);
	}
	else
	{
		close(pipex->fd[0]);
		if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
			free_pipex_exit(pipex);
	}
	cmd = find_cmd(pipex->cmds, idx);
	if (!cmd)
		free_pipex_exit(pipex);
	execve(cmd->cmd, cmd->cmd_strs, envp);
}

void	launch_processes(t_pipex_b *pipex, char **envp)
{
	int	i;

	pipex->pids = get_pids(pipex->cmd_count);
	if (!pipex->pids)
		free_pipex_exit(pipex);
	pipex->fd = get_fd();
	i = -1;
	while (++i < pipex->cmd_count)
	{
		pipex->pids[i] = fork();
		if (pipex->pids[i] == -1)
			free_pipex(pipex);
		if (pipex->pids[i] == 0)
			child_processes(pipex, envp, i);
		if (dup2(STDIN_FILENO, pipex->fd[0]) == -1)
			free_pipex_exit(pipex);
	}
	i = -1;
	while (++i < pipex->cmd_count)
		wait(NULL);
	close_pipes(pipex->fd);
}
