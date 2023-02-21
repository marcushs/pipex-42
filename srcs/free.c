#include "../includes/pipex.h"

void	free_prev_arr(void **arr, int i)
{
	i--;
	while (i >= 0)
	{
		free(((void **)*arr)[i]);
		((void **)*arr)[i] = NULL;
		i--;
	}
	free(*arr);
	*arr = NULL;
}

void	free_2d_arr(void **arr)
{
	int	i;

	i = -1;
	while (((void **)*arr)[++i])
	{
		free(((void **)*arr)[i]);
		((void **)*arr)[i] = NULL;
	}
	free(*arr);
	*arr = NULL;
}

void	print_msg_exit(char *msg)
{
	ft_printf("%s", msg);
	exit(EXIT_FAILURE);
}

void	perror_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	free_pipex(t_pipex *pipex)
{
	free_2d_arr((void **)&pipex->path);
	free_2d_arr((void **)&pipex->cmd1_strs);
	free_2d_arr((void **)&pipex->cmd2_strs);
	free(pipex->prefix);
	pipex->prefix = NULL;
	free(pipex->cmd1);
	pipex->cmd1 = NULL;
	free(pipex->cmd2);
	pipex->cmd2 = NULL;
	free(pipex->fd);
	pipex->fd = NULL;
	exit(0);
}
