/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:42:59 by hleung            #+#    #+#             */
/*   Updated: 2023/04/20 14:34:16 by hleung           ###   ########lyon.fr   */
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
	return (join);
}

void	write_str_to_pipe(char *str)
{
	int	*fd;

	fd = get_fd();
	dup2(STDOUT_FILENO, fd[1]);
	if (write(fd[1], str, ft_strlen(str)) == -1)
		ft_printf("cant write\n");
	close(fd[0]);
	close(fd[1]);
	free(fd);
	free(str);
}

void	start_here_doc(char *limiter)
{
	char	*line;
	char	*rtn_str;

	rtn_str = NULL;
	while (1)
	{
		ft_printf("pipe heredoc> ");
		line = get_next_line(0);
		if (!line)
			exit(0);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			line = NULL;
			write_str_to_pipe(rtn_str);
			exit(0);
		}
		rtn_str = ft_join_line(rtn_str, line);
		if (!rtn_str)
			free_null_exit(&line);
		free(line);
	}
}
