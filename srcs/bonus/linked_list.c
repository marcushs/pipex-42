#include "../../includes/pipex_b.h"

static t_cmds	*lst_new(char *arg, int index)
{
	t_cmds	*new;

	new = (t_cmds *)malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->cmd_strs = ft_split(arg, ' ');
	if (!new->cmd_strs)
		return (free(new), new = NULL, NULL);
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

void	lst_clear(t_cmds **head, void(*f)(void **))
{
	t_cmds	*tmp;

	if (!*head || !*f)
		return ;
	tmp = *head;
	while (tmp)
	{
		f((void **)&tmp->cmd_strs);
		tmp = tmp->next;
		free(*head);
		*head = tmp;
	}
}

void	lst_addback(t_cmds **head, char *arg, int index)
{
	t_cmds	*new;
	t_cmds	*last;

	new = lst_new(arg, index);
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
		lst_clear(head, &free_2d_arr);
}

void	lst_print(t_cmds *head)
{
	t_cmds	*tmp;
	int		i = 0;

	tmp = head;
	while (tmp)
	{
		head = tmp->next;
		printf("Index: %d, ", tmp->index);
		while (tmp->cmd_strs[i])
		{
			printf("%s ", tmp->cmd_strs[i]);
			i++;
		}
		i = 0;
		printf("\n");
		tmp = head;
	}
}