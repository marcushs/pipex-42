/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:17:38 by hleung            #+#    #+#             */
/*   Updated: 2023/04/21 14:59:22 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

void	free_null_exit(char **str)
{
	free(*str);
	*str = NULL;
	exit(0);
}

void	print_msg_exit(char *msg)
{
	ft_printf("%s", msg);
	exit(EXIT_FAILURE);
}

void	free_pipex(t_pipex_b *pipex)
{
	free_2d_arr((void **)&pipex->path);
	lst_clear(&pipex->cmds, &free_2d_arr);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	free(pipex->pids);
	pipex->pids = NULL;
}

void	free_pipex_exit(t_pipex_b *pipex)
{
	free_pipex(pipex);
	exit(0);
}
