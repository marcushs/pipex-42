/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:42:59 by hleung            #+#    #+#             */
/*   Updated: 2023/04/26 18:57:17 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_b.h"

static char	*ft_join_line(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;
	size_t	s2_len;

	s2_len = ft_strlen(s2);
	if (!s1)
		join = (char *)malloc(s2_len + 1);
	else
		join = (char *)malloc(ft_strlen(s1) + s2_len + 1);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		join[i++] = s1[j++];
	j = 0;
	while (j < s2_len)
		join[i++] = s2[j++];
	join[i] = 0;
	return (free(s1), s1 = NULL, join);
}

void	write_str_to_pipe(t_pipex_b *pipex, char *str)
{
	if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
		free_pipex_exit(pipex);
	close(pipex->fd[0]);
	if (write(pipex->fd[1], str, ft_strlen(str)) == -1)
	{
		free(str);
		free_pipex_exit(pipex);
	}
	close(pipex->fd[1]);
}

char	*start_here_doc(int cmd_count, char *limiter)
{
	char	*line;
	char	*rtn_str;
	size_t	lim_len;
	int		i;

	rtn_str = NULL;
	lim_len = ft_strlen(limiter);
	while (1)
	{
		i = cmd_count;
		while (--i > 0)
			ft_printf("pipe ");
		ft_printf("heredoc> ");
		line = get_next_line(0);
		if (!line)
			return (NULL);
		if (ft_strlen(line) - 1 == lim_len && \
		ft_strncmp(line, limiter, lim_len) == 0)
			return (free(line), line = NULL, rtn_str);
		rtn_str = ft_join_line(rtn_str, line);
		if (!rtn_str)
			return (free(line), line = NULL, NULL);
		free(line);
	}
}

void	launch_heredoc_process(t_pipex_b *pipex, int ac, char **av, char **env)
{
	char	*str;

	pipex->hd_idx = 1;
	pipex->cmd_count = ac - 4;
	str = start_here_doc(pipex->cmd_count, av[2]);
	if (!str)
		free_pipex_exit(pipex);
	if (pipe(pipex->fd) == -1)
		free_pipex_exit(pipex);
	write_str_to_pipe(pipex, str);
	free(str);
	pipex->outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (pipex->outfile && access(av[ac - 1], R_OK) == -1)
		ft_printf("Cannot open %s: Permission denied\n", av[ac - 1]);
	pipex->path = find_path(env);
	pipex->cmds = args_to_lst(pipex, av);
	if (!pipex->cmds)
		free_pipex_exit(pipex);
	launch_processes(pipex, env);
	free_pipex(pipex);
	exit(EXIT_SUCCESS);
}
