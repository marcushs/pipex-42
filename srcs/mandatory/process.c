#include "../../includes/pipex.h"

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
	// int	err;
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
	execve(pipex->cmd1, pipex->cmd1_strs, envp);
	// err = errno;
	// strerror(err);
	// free_pipex(pipex);
	// exit(err);
}

void	second_child(t_pipex *pipex, char **envp)
{
	// int	err;
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
	printf("%s\n", pipex->cmd2);
	execve(pipex->cmd2, pipex->cmd2_strs, envp);
	// err = errno;
	// strerror(err);
	// free_pipex(pipex);
	// exit(err);
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
