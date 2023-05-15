/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:12:00 by hleung            #+#    #+#             */
/*   Updated: 2023/05/15 11:11:12 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_strings(char const *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
			count++;
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (count);
}

static int	ft_strlen_sep(char const *s)
{
	int	i;

	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	return (i);
}

static char	*make_word(char const *s)
{
	char	*word;
	int		i;
	int		len;

	len = ft_strlen_sep(s);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

static char	**ft_splitter(char **strs, char const *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (*s)
		{
			strs[i] = make_word(s);
			if (!strs[i])
			{
				while (i >= 0)
					free(strs[i--]);
				free(strs);
				return (NULL);
			}
			i++;
		}
		while (*s && !ft_isspace(*s))
			s++;
	}
	strs[i] = 0;
	return (strs);
}

char	**ft_split_space(char const *s)
{
	char	**new_strs;

	if (!s || s[0] == 0)
		return (NULL);
	new_strs = (char **)malloc(sizeof(char *) * (count_strings(s) + 1));
	if (!new_strs)
		return (NULL);
	return (ft_splitter(new_strs, s));
}
