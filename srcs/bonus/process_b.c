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

void	child_processes(t_pipex_b *pipex, char **envp)
{
	
}

void	launch_processes(t_pipex_b *pipex, char **envp)
{
	int	i;

	pipex->fd = get_fd();
	if (!pipex->fd)
		free_pipex(pipex);
	pipex->pids = get_pids(pipex->cmd_count);
	if (!pipex->pids)
		free_pipex(pipex);
	i = -1;
	while (++i < pipex->cmd_count)
	{
		pipex->pids[i] = fork();
		if (pipex->pids[i] == -1)
		if (pipex->pids[i] == 0)
		{
			if (i == 0)
				
		}
		
	}
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
