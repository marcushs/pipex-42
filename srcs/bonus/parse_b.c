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
	//char	**tmp;

	head = NULL;
	i = 2 + pipex->hd_idx;
	j = -1;
	while (++j < pipex->cmd_count)
		lst_addback(&head, argv[i++], j);
	return (head);
}

// void	dup_argv_cmds_strs(t_pipex_b *pipex, char **argv)
// {
// 	int		i;
// 	int		j;

// 	pipex->cmds_strs = (char **)malloc(sizeof(char *) * pipex->cmd_count);
// 	if (!pipex->cmds_strs)
// 		free_pipex_exit(pipex);
// 	i = 2 + pipex->hd_idx;
// 	j = -1;
// 	while (++j < pipex->cmd_count)
// 	{
// 		pipex->cmds_strs[j] = argv[i++];
// 		if (!pipex->cmds_strs[j])
// 			free_pipex_exit(pipex);
// 	}
// }

//void	parse_cmd_for_exec(t_pipex_b *pipex, char **argv)
// {
// 	char	**tmp;
// 	int		i;

// 	dup_argv_cmds_strs(pipex, argv);
// 	pipex->cmds = (char **)malloc(sizeof(char *) * pipex->cmd_count);
// 	if (!pipex->cmds)
// 		free_pipex_exit(pipex);
// 	i = -1;
// 	while (++i < pipex->cmd_count)
// 	{
// 		tmp = ft_split(pipex->cmds_strs[i], ' ');
// 		// if (!tmp)
// 		// 	//faire qqch
// 		if (!check_bin(tmp[0], pipex->path))
// 		{
// 			free_2d_arr((void **)tmp);
// 			free_pipex_exit(pipex);
// 		}
// 		pipex->cmds[i] = ft_strdup(tmp[0]);
// 		if (!pipex->cmds[i])
// 			free_pipex_exit(pipex);
// 		free_2d_arr((void **)tmp);
// 	}
// }
