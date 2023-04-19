/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:42:59 by hleung            #+#    #+#             */
/*   Updated: 2023/04/18 15:11:15 by hleung           ###   ########lyon.fr   */
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

char	*start_here_doc(char *limiter)
{
	char	*line;
	char	*rtn_str;

	while (1)
	{
		ft_printf("pipe heredoc> ");
		line = get_next_line(0);
		rtn_str = ft_join_line(rtn_str, line);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			return (free(line), line = NULL, rtn_str);
		free(line);
	}
}
