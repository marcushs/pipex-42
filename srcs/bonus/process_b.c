/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:18:09 by hleung            #+#    #+#             */
/*   Updated: 2023/04/21 14:37:31 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_b.h"

static int	*get_pids(int cmd_count)
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
static void	close_pipes(int	fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

static void	dup2s(t_pipex_b *pipex)
{
	if (pipex->infile == -1)
	{
		close(pipex->fd[1]);
		if (pipex->outfile != -1)
			close(pipex->outfile);
		free_pipex_exit(pipex);
	}
	if (dup2(pipex->infile, STDIN_FILENO) == -1)
		free_pipex_exit(pipex);
	close(pipex->infile);
	if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
		free_pipex_exit(pipex);
	close(pipex->fd[1]);
}
static void	redirect_fd(t_pipex_b *pipex, int idx)
{
	if (idx == 0)
	{
		if (!pipex->hd_idx)
		{
			close(pipex->fd[0]);
			dup2s(pipex);
		}
		else if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
			free_pipex_exit(pipex);
		close(pipex->fd[1]);
	}
	else if (idx == pipex->cmd_count - 1)
	{
		close(pipex->fd[1]);
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			free_pipex_exit(pipex);
		close(pipex->outfile);
	}
	else
	{
		close(pipex->fd[0]);
		if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
			free_pipex_exit(pipex);
		close(pipex->fd[1]);
	}
}
void	child_processes(t_pipex_b *pipex, char **envp, int idx)
{
	t_cmds	*cmd;

	redirect_fd(pipex, idx);
	cmd = find_cmd(pipex->cmds, idx);
	if (!cmd->cmd)
		free_pipex_exit(pipex);
	execve(cmd->cmd, cmd->cmd_strs, envp);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	close_pipes(pipex->fd);
	free_pipex_exit(pipex);
}

void	launch_processes(t_pipex_b *pipex, char **envp)
{
	int	i;

	pipex->pids = get_pids(pipex->cmd_count);
	if (!pipex->pids)
		free_pipex_exit(pipex);
	i = -1;
	while (++i < pipex->cmd_count)
	{
		if (pipe(pipex->fd) == -1)
			free_pipex_exit(pipex);
		pipex->pids[i] = fork();
		if (pipex->pids[i] == -1)
			free_pipex(pipex);
		if (pipex->pids[i] == 0)
			child_processes(pipex, envp, i);
		if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
			free_pipex_exit(pipex);
		close_pipes(pipex->fd);
		wait(NULL);
	}
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
}
