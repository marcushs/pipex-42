/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:17:45 by hleung            #+#    #+#             */
/*   Updated: 2023/05/15 11:54:36 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_b.h"

static t_cmds	*lst_new(char *arg, int index, char **path)
{
	t_cmds	*new;

	new = (t_cmds *)malloc(sizeof(t_cmds));
	if (!new)
	{
		ft_putstr_fd("Malloc error\n", 1);
		return (NULL);
	}
	new->cmd = NULL;
	new->cmd_strs = NULL;
	if ((!arg[0]) | all_space(arg))
		ft_printf("Command not found: %s\n", arg);
	else
		new->cmd_strs = ft_split_space(arg);
	if (new->cmd_strs)
		new->cmd = check_bin(new->cmd_strs[0], path);
	new->index = index;
	new->next = NULL;
	return (new);
}

static t_cmds	*lst_last(t_cmds *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}

void	lst_clear(t_cmds **head)
{
	t_cmds	*tmp;

	if (!*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		free(tmp->cmd);
		tmp->cmd = NULL;
		free_2d_arr((void **)&tmp->cmd_strs);
		tmp = tmp->next;
		free(*head);
		*head = tmp;
	}
}

void	lst_addback(t_cmds **head, char *arg, int index, char **path)
{
	t_cmds	*new;
	t_cmds	*last;

	new = lst_new(arg, index, path);
	if (new)
	{
		if (!*head)
		{
			*head = new;
			return ;
		}
		last = lst_last(*head);
		last->next = new;
	}
	else
		lst_clear(head);
}

t_cmds	*find_cmd(t_cmds *head, int idx)
{
	t_cmds	*tmp;

	tmp = head;
	while (tmp)
	{
		head = tmp->next;
		if (idx == tmp->index)
			return (tmp);
		tmp = head;
	}
	return (NULL);
}
