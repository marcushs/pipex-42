#include "../../includes/pipex_b.h"

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

	if (!((void **)*arr))
		return ;
	i = -1;
	while (((void **)*arr)[++i])
	{
		free(((void **)*arr)[i]);
		((void **)*arr)[i] = NULL;
	}
	free(*arr);
	*arr = NULL;
}

void	strerror_exit(void)
{
	strerror(errno);
	exit(errno);
}

void	print_msg_exit(char *msg)
{
	ft_printf("%s", msg);
	exit(EXIT_FAILURE);
}

void	free_pipex(t_pipex_b *pipex)
{
	free_2d_arr((void **)&pipex->path);
	free_2d_arr((void **)&pipex->cmds_strs);
	free_2d_arr((void **)&pipex->cmds);
	free_2d_arr((void **)&pipex->fds);
	free(pipex->pids);
	pipex->pids = NULL;

}
