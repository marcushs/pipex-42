#include "../includes/pipex.h"

int	find_2d_arr_size(void **arr)
{
	int	size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

char	*get_prefix(char **strs)
{
	int		i;
	char	*prefix;

	i = -1;
	while (strs[++i])
	{
		if (ft_strncmp("/usr/bin", strs[i], 8) == 0)
		{
			prefix = ft_strdup(strs[i]);
			if (prefix)
				return (prefix);
		}
	}
	return (NULL);
}

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


//this function is going to parse a cmd + its options into a char **
void	parse_cmd_for_exec(t_pipex *pipex, char **argv)
{
	char	*tmp;

	pipex->cmd1_strs = ft_split(argv[2], ' ');
	pipex->cmd2_strs = ft_split(argv[3], ' ');
	if (!pipex->cmd1_strs || !pipex->cmd2_strs)
		free_pipex(pipex);//need free the rest and exit
	tmp = ft_strjoin(pipex->prefix, "/");
	if (!tmp)
		free_pipex(pipex);//need free the rest and exit
	pipex->cmd1 = ft_strjoin(tmp, pipex->cmd1_strs[0]);
	pipex->cmd2 = ft_strjoin(tmp, pipex->cmd2_strs[0]);
	if (!pipex->cmd1 || !pipex->cmd2)
		free_pipex(pipex);//need free the rest and exit
	free(tmp);
	tmp = NULL;
	if (!check_bin(pipex->cmd1) || !check_bin(pipex->cmd2))
	{
		perror("Error");
		free_pipex(pipex);
	}
}
