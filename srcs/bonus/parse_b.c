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

void	parse_cmd_for_exec(t_pipex_b *pipex, char **argv, int argc)
{
	int	i;
	int	j;
	char	**tmp;
	(void)argc;

	pipex->cmds_strs = (char **)malloc(sizeof(char *) * pipex->cmd_count);
	pipex->cmds = (char **)malloc(sizeof(char *) * pipex->cmd_count);
	tmp = (char **)malloc(sizeof(char *) * pipex->cmd_count);
	
	if (!pipex->cmds_strs || !pipex->cmds)
	{
		free_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	i = 2 + pipex->hd_idx;
	j = -1;
	while (++j < pipex->cmd_count)
	{
		pipex->cmds_strs[j] = argv[i++];
		if (!pipex->cmds_strs[j])
		{
			free_pipex(pipex);
			exit(EXIT_FAILURE);
		}
	}
	i = -1;
	while (++i < pipex->cmd_count)
	{
		tmp = ft_split(pipex->cmds_strs[i], ' ');
		// if (!tmp)
		// 	//faire qqch
		if (check_bin(tmp[0], pipex->path) != NULL)
		pipex->cmds[i] = ft_strdup(tmp[0]);
		// if (!pipex->cmds[i])
		// {
		// 	free_pipex(pipex);
		// 	exit(0);
		// }
		free_2d_arr((void **)tmp);
	}
}
