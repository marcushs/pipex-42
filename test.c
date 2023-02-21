#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

char	*find_path(char **envp)
{
	char	*path;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (strncmp("PATH", envp[i], 4) == 0)
			return (envp[i] + 5);
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char *args[] = {"ls", "-l", NULL};
	char *env[] = {NULL};

	if (execve("/home/marcus/.nvm/versions/node/v16.15.0/bin/ls", args, env) == -1) {
        perror("Error executing command");
        exit(EXIT_FAILURE);
    }
	return (0);
}
