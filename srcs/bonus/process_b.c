#include "../../includes/pipex_b.h"

int	*get_fd()
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
	if (dup2(wr, STDOUT_FILENO) == -1)
		free_pipex_exit(pipex);
}

void	child_processes(t_pipex_b *pipex, char **envp, int idx)
{
	t_cmds	*cmd;

	if (idx == 0)
		dup2s(pipex, pipex->infile, pipex->fd[1]);
	else if (idx == pipex->cmd_count - 1)
		dup2s(pipex, pipex->fd[0], pipex->outfile);
	else
		dup2(pipex, pipex->fd[0], STDOUT_FILENO);
	close_pipes(pipex->fd);
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
		free_pipex(pipex);
	pipex->fd = get_fd();
	i = -1;
	while (++i < pipex->cmd_count)
	{
		pipex->pids[i] = fork();
		if (pipex->pids[i] == -1)
			free_pipex(pipex);
		if (pipex->pids[i] == 0)
			child_processes(pipex, envp, i);
		dup2(pipex->pid)
	}
	close_pipes(pipex->fd);
	wait_status(pipex, 1);
	wait_status(pipex, 2);
}
