/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:56:05 by hleung            #+#    #+#             */
/*   Updated: 2023/05/03 16:11:10 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

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

void	print_msg_exit(char *msg)
{
	ft_printf("%s", msg);
	exit(EXIT_FAILURE);
}

void	free_pipex(t_pipex *pipex)
{
	free_2d_arr((void **)&pipex->path);
	free_2d_arr((void **)&pipex->cmd1_strs);
	free_2d_arr((void **)&pipex->cmd2_strs);
	free(pipex->cmd1);
	pipex->cmd1 = NULL;
	free(pipex->cmd2);
	pipex->cmd2 = NULL;
	free(pipex->fd);
	pipex->fd = NULL;
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
}

void	free_pipex_exit(t_pipex *pipex)
{
	free_pipex(pipex);
	exit(0);
}
