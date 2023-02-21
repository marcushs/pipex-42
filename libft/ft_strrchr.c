/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:50:45 by hleung            #+#    #+#             */
/*   Updated: 2022/11/15 14:58:56 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	last;

	last = 0;
	while (s[last])
		last++;
	while (last >= 0)
	{
		if (s[last] == (unsigned char)c)
			return ((char *)&s[last]);
		last--;
	}
	return (NULL);
}
