/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:55:31 by hleung            #+#    #+#             */
/*   Updated: 2023/05/15 12:54:13 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_B_H
# define PIPEX_B_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_cmds
{
	char			*cmd;
	char			**cmd_strs;
	int				index;
	struct s_cmds	*next;
}				t_cmds;

typedef struct s_pipex_b
{
	int		infile;
	int		outfile;
	char	**path;
	t_cmds	*cmds;
	int		cmd_count;
	int		fd[2];
	int		hd_idx;
	pid_t	*pids;
}				t_pipex_b;

//parse
char	**find_path(char **envp);
char	*check_bin(char *cmd, char **path);
t_cmds	*args_to_lst(t_pipex_b *pipex, char **argv);
t_cmds	*find_cmd(t_cmds *head, int idx);
int		*get_pids(int cmd_count);
int		all_space(char *s);
//linked list
void	lst_addback(t_cmds **head, char *arg, int index, char **path);
void	lst_clear(t_cmds **head);
//free
void	free_2d_arr(void **arr);
void	free_pipex(t_pipex_b *pipex);
void	free_pipex_exit(t_pipex_b *pipex);
//process
void	close_pipes(int fd[2]);
void	launch_processes(t_pipex_b *pipex, char **envp);
//here_doc
void	launch_heredoc_process(t_pipex_b *pipex, int ac, char **av, char **ep);
char	*start_here_doc(int cmd_count, char *limiter);
#endif
