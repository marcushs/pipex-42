#include "../includes/pipex.h"

int	check_bin(char *cmd)
{
	if (access(cmd, X_OK) == -1)
	{
		printf("Cant find command\n");
		return (0);
	}
	return (1);
}
