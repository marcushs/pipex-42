/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:42:59 by hleung            #+#    #+#             */
/*   Updated: 2023/04/21 12:10:58 by hleung           ###   ########lyon.fr   */
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
	pipex->fd = get_fd();
	dup2(pipex->fd[0], STDIN_FILENO);
	if (write(pipex->fd[1], str, ft_strlen(str)) == -1)
	{
		free(str);
		free_pipex_exit(pipex);
	}
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	free(pipex->fd);
	pipex->fd = NULL;
	free(str);
	str = NULL;
}

char	*start_here_doc(char *limiter)
{
	char	*line;
	char	*rtn_str;
	size_t	lim_len;

	rtn_str = NULL;
	lim_len = ft_strlen(limiter);
	while (1)
	{
		ft_printf("pipe heredoc> ");
		line = get_next_line(0);
		if (!line)
			return (NULL);
		if (ft_strlen(line) - 1 == lim_len && ft_strncmp(line, limiter, lim_len) == 0)
			return (free(line), line = NULL, rtn_str);
		rtn_str = ft_join_line(rtn_str, line);
		if (!rtn_str)
			return (free(line), line = NULL, NULL);
		free(line);
	}
}

void	launch_heredoc_process(t_pipex_b *pipex, int argc, char **argv, char **envp)
{
	char	*str;

	pipex->hd_idx = 1;
	pipex->cmd_count = argc - 4;
	str = start_here_doc(argv[2]);
	if (!str)
		free_pipex_exit(pipex);
	pipex->outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (pipex->outfile && access(argv[argc - 1], R_OK) == -1)
		ft_printf("Cannot open %s: Permission denied\n", argv[argc - 1]);
	pipex->path = find_path(envp);
	pipex->cmds = args_to_lst(pipex, argv);
	if (!pipex->cmds)
		free_pipex_exit(pipex);
	write_str_to_pipe(pipex, str);
	launch_processes(pipex, envp);
	free_pipex(pipex);
	exit(EXIT_SUCCESS);
}
