/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:14:15 by hleung            #+#    #+#             */
/*   Updated: 2022/11/25 09:35:29 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*cpy;
	int		len_start;
	int		len_end;
	int		i;

	if (!s1)
		return (NULL);
	len_start = 0;
	len_end = ft_strlen(s1);
	while (s1[len_start] && ft_check_set(s1[len_start], set))
		len_start++;
	while (len_end > len_start && ft_check_set(s1[len_end - 1], set))
		len_end--;
	cpy = (char *)malloc(sizeof(char) * (len_end - len_start + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (len_end > len_start)
		cpy[i++] = s1[len_start++];
	cpy[i] = 0;
	return (cpy);
}
