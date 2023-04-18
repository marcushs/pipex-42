/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:07:32 by hleung            #+#    #+#             */
/*   Updated: 2023/04/18 12:10:24 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_b.h"

int	wait_status(t_pipex_b *pipex, int pid)
{
	int	wstatus;
	int	id;

	id = pid;
	waitpid(id, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		if (WEXITSTATUS(wstatus) != EXIT_SUCCESS)
		{
			free_pipex(pipex);
			return (WEXITSTATUS(wstatus));
		}
	}
	return (WEXITSTATUS(wstatus));
}
