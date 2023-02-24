#include "../../includes/pipex_b.h"

char	*check_bin(char *cmd, char **path)
{
	char	*tmp;
	char	*rtn_cmd;
	int		i;

	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (NULL);
		rtn_cmd = ft_strjoin(tmp, cmd);
		if (!rtn_cmd)
			return (free(tmp), tmp = NULL, NULL);
		if (access(rtn_cmd, X_OK) == 0)
			return (free(tmp), tmp = NULL, rtn_cmd);
		else
		{
			free(tmp);
			tmp = NULL;
			free(rtn_cmd);
			rtn_cmd = NULL;
		}
	}
	perror("Command not found");
	return (NULL);
}
