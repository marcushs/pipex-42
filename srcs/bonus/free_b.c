/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:17:38 by hleung            #+#    #+#             */
/*   Updated: 2023/04/25 16:48:08 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_b.h"

void	close_pipes(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

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

void	free_pipex(t_pipex_b *pipex)
{
	free_2d_arr((void **)&pipex->path);
	lst_clear(&pipex->cmds);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
}

void	free_pipex_exit(t_pipex_b *pipex)
{
	free_pipex(pipex);
	exit(0);
}
