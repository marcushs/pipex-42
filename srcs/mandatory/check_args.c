#include "../../includes/pipex.h"

char	*join_strs(char *path, char *cmd)
{
	char	*tmp;
	char	*rtn_cmd;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	rtn_cmd = ft_strjoin(tmp, cmd);
	if (!rtn_cmd)
		return (free(tmp), tmp = NULL, NULL);
	return (rtn_cmd);
}
int	check_full_path(char *cmd)
{
	if (ft_strchr_int(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (1);
		else
		{
			ft_printf("command not found: %s\n", cmd);
			return (0);
		}
	}
	re
}

char	*check_bin(char *cmd, char **path)
{
	char	*rtn_cmd;
	int		i;

	if (check_full_path(cmd))
		return (cmd);
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
	ft_printf("command not found: %s\n", cmd);
	return (NULL);
}
