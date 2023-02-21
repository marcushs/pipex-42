/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:20:46 by hleung            #+#    #+#             */
/*   Updated: 2022/11/13 19:48:58 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	if (!dst && !dstsize)
		return (ft_strlen(src));
	len = 0;
	while (dst[len] && len < dstsize)
		len++;
	i = 0;
	while (src[i] && dstsize && len + i < dstsize - 1)
	{
		dst[len + i] = src[i];
		i++;
	}
	if (len < dstsize)
		dst[len + i] = 0;
	i = 0;
	while (src[i])
		i++;
	return (len + i);
}
