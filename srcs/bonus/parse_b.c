/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:17:50 by hleung            #+#    #+#             */
/*   Updated: 2023/04/17 14:17:51 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_b.h"

char	**find_path(char **envp)
{
	char	**strs;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
		{
			strs = ft_split(envp[i] + 5, ':');
			if (strs)
				return (strs);
		}
	}
	return (NULL);
}

t_cmds	*args_to_lst(t_pipex_b *pipex, char **argv)
{
	t_cmds	*head;
	int		i;
	int		j;

	head = NULL;
	i = 2 + pipex->hd_idx;
	j = -1;
	while (++j < pipex->cmd_count)
		lst_addback(&head, argv[i++], j, pipex->path);
	return (head);
}
