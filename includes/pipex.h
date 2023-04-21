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
#define ARG_NUM_ERR "Wrong number of argument\n"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**path;
	char	**cmd1_strs;
	char	**cmd2_strs;
	char	*cmd1;
	char	*cmd2;
	int		*fd;
	pid_t	pid1;
	pid_t	pid2;
}				t_pipex;

int		check_args(int argc, char **argv);
void	parse_cmd_for_exec(t_pipex *pipex, char **argv);
char	*check_bin(char *cmd, char **path);
char	**find_path(char **envp);
void	launch_processes(t_pipex *pipex, char **envp);
int		find_2d_arr_size(void **arr);
int		wait_status(t_pipex *pipex, int pid);
//free
void	free_2d_arr(void **arr);
void	print_msg_exit(char *msg);
void	strerror_exit(void);
void	free_pipex(t_pipex *pipex);
void	free_prev_arr(void **arr, int i);
void	free_pipex_exit(t_pipex *pipex);
#endif
