/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bin_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:17:34 by hleung            #+#    #+#             */
/*   Updated: 2023/04/18 11:08:23 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_b.h"

static char	*join_strs(char *path, char *cmd)
{
	char	*tmp;
	char	*rtn_cmd;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	rtn_cmd = ft_strjoin(tmp, cmd);
	if (!rtn_cmd)
		return (free(tmp), tmp = NULL, NULL);
	free(tmp);
	tmp = NULL;
	return (rtn_cmd);
}

static char	*check_full_path(char *cmd)
{
	char	*rtn_cmd;

	if (access(cmd, X_OK) == 0)
	{
		rtn_cmd = ft_strdup(cmd);
		if (rtn_cmd)
			return (rtn_cmd);
	}
	ft_printf("Command not found: %s\n", cmd);
	return (NULL);
}

char	*check_bin(char *cmd, char **path)
{
	char	*rtn_cmd;
	int		i;

	if (cmd)
	{
		if (ft_strchr_int(cmd, '/'))
		{
			rtn_cmd = check_full_path(cmd);
			return (rtn_cmd);
		}
		i = -1;
		while (path && path[++i])
		{
			rtn_cmd = join_strs(path[i], cmd);
			if (access(rtn_cmd, X_OK) == 0)
				return (rtn_cmd);
			else
			{
				free(rtn_cmd);
				rtn_cmd = NULL;
			}
		}
	}
	ft_printf("Command not found: %s\n", cmd);
	return (NULL);
}

