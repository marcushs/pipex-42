#ifndef PIPEX_H
#define PIPEX_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include "../libft/libft.h"

typedef struct s_pipex_b
{
	int		infile;
	int		outfile;
	char	**path;
	char	**cmds;
	char	**cmds_strs;
	int		cmd_count;
	int		**fds;
	int		hd_idx;
	pid_t	*pids;
}				t_pipex_b;

char	**find_path(char **envp);
void	parse_cmd_for_exec(t_pipex_b *pipex, char **argv, int argc);
char	*check_bin(char *cmd, char **path);
void	free_2d_arr(void **arr);
void	free_pipex(t_pipex_b *pipex);
#endif
