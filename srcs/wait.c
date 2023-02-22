#include "../includes/pipex.h"

int	wait_status(t_pipex *pipex, int	pid)
{
	int	wstatus;
	int	id;

	id = pipex->pid1;
	if (pid == 2)
		id = pipex->pid2;
	waitpid(id, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		if (WEXITSTATUS(wstatus) == EXIT_FAILURE)
		{
			free_pipex(pipex);
			return (WEXITSTATUS(wstatus));
		}
	}
	return (WEXITSTATUS(wstatus));
}
