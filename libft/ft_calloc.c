/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:10:38 by hleung            #+#    #+#             */
/*   Updated: 2022/11/28 11:31:47 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	total_size;
	size_t	i;

	if (count != 0 && size > SIZE_MAX / count)
		return (NULL);
	total_size = count * size;
	mem = malloc(total_size);
	if (!mem)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		((char *)mem)[i] = 0;
		i++;
	}
	return (mem);
}
