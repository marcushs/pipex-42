/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:56:42 by hleung            #+#    #+#             */
/*   Updated: 2023/04/17 14:01:18 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	wait_status(t_pipex *pipex, int pid)
{
	int	wstatus;
	int	id;

	id = pipex->pid1;
	if (pid == 2)
		id = pipex->pid2;
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
