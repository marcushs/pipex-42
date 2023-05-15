/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:59:14 by hleung            #+#    #+#             */
/*   Updated: 2023/05/15 11:46:15 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	all_space(char *s)
{
	while (*s && ft_isspace(*s))
		s++;
	if (*s && !ft_isspace(*s))
		return (0);
	return (1);
}

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
	if ((!argv[2][0]) | all_space(argv[2]))
		ft_printf("Command not found: %s\n", argv[2]);
	else
	{
		pipex->cmd1_strs = ft_split_space(argv[2]);
		pipex->cmd1 = check_bin(pipex->cmd1_strs[0], pipex->path);
	}
	if ((!argv[3][0]) | all_space(argv[3]))
		ft_printf("Command not found: %s\n", argv[3]);
	else
	{
		pipex->cmd2_strs = ft_split_space(argv[3]);
		pipex->cmd2 = check_bin(pipex->cmd2_strs[0], pipex->path);
	}
}
