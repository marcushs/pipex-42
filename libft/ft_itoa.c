/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:06:00 by hleung            #+#    #+#             */
/*   Updated: 2022/11/25 09:39:13 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int				i;
	unsigned int	nb;

	nb = n;
	i = 0;
	if (n == 0)
		return (++i);
	if (n < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*a;
	int				len;
	unsigned int	nb;

	nb = n;
	len = ft_count(n);
	a = (char *)malloc(sizeof(char) * (len + 1));
	if (!a)
		return (NULL);
	if (n == 0)
		a[0] = '0';
	if (n < 0)
	{
		nb *= -1;
		a[0] = '-';
	}
	a[len] = 0;
	len--;
	while (nb > 0)
	{
		a[len] = nb % 10 + '0';
		nb /= 10;
		len--;
	}
	return (a);
}
