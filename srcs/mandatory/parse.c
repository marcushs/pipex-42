/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:59:14 by hleung            #+#    #+#             */
/*   Updated: 2023/04/21 13:48:16 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	find_2d_arr_size(void **arr)
{
	int	size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

char	**find_path(char **envp)
{
	char	**strs;
	int		i;

	if (!envp)
		return (NULL);
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

void	parse_cmd_for_exec(t_pipex *pipex, char **argv)
{
	pipex->cmd1_strs = ft_split(argv[2], ' ');
	pipex->cmd2_strs = ft_split(argv[3], ' ');
	if (!pipex->cmd1_strs || !pipex->cmd2_strs)
	{
		free_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	pipex->cmd1 = check_bin(pipex->cmd1_strs[0], pipex->path);
	pipex->cmd2 = check_bin(pipex->cmd2_strs[0], pipex->path);
}
