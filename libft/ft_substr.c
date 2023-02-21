/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:57:27 by hleung            #+#    #+#             */
/*   Updated: 2022/11/22 17:57:15 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		new_str = (char *)malloc(sizeof(char) * 1);
	else if (len > ft_strlen(s) - start)
		new_str = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len && i < ft_strlen(s) - start && start < ft_strlen(s))
	{
		new_str[i] = (s + start)[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}
