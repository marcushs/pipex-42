#include "../includes/pipex.h"

void	close_pipes(int	*fd)
{
	close(fd[0]);
	close(fd[1]);
}

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

void	first_child(t_pipex *pipex, char **envp)
{
	close(pipex->fd[0]);
	dup2(pipex->infile, STDIN_FILENO);
	dup2(pipex->fd[1], STDOUT_FILENO);
	execve(pipex->cmd1, pipex->cmd1_strs, envp);
}

void	second_child(t_pipex *pipex, char **envp)
{
	close(pipex->fd[1]);
	dup2(pipex->fd[0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	execve(pipex->cmd2, pipex->cmd2_strs, envp);
}

void	launch_processes(t_pipex *pipex, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	pipex->fd = get_fd();
	if (!pipex->fd)
		free_pipex(pipex);
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("Error forking process");
		free_pipex(pipex);
	}
	if (pid1 == 0)
		first_child(pipex, envp);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("Error forking process");
		free_pipex(pipex);
	}
	if (pid2 == 0)
		second_child(pipex, envp);
	close_pipes(pipex->fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
