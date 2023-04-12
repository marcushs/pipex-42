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

typedef struct s_cmds
{
	char		*cmd;
	char		**cmd_strs;
	int			index;
	struct s_cmds	*next;
}				t_cmds;

typedef struct s_pipex_b
{
	int		infile;
	int		outfile;
	char	**path;
	t_cmds	*cmds;
	int		cmd_count;
	int		*fd;
	int		hd_idx;
	pid_t	*pids;
}				t_pipex_b;

char	**find_path(char **envp);
char	*check_bin(char *cmd, char **path);
void	free_2d_arr(void **arr);
void	free_pipex(t_pipex_b *pipex);
void	free_pipex_exit(t_pipex_b *pipex);
void	lst_clear(t_cmds **head, void(*f)(void **));
void	lst_addback(t_cmds **head, char *arg, int index);
t_cmds	*args_to_lst(t_pipex_b *pipex, char **argv);
void	lst_print(t_cmds *head);
t_cmds	*find_cmd(t_cmds *head, int idx);
#endif
