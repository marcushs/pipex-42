/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcus <marcus@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:55:04 by hleung            #+#    #+#             */
/*   Updated: 2023/02/19 20:07:48 by marcus           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putadd(unsigned long nbr, char *charset)
{
	int	len;

	len = 0;
	if (nbr == 0)
	{
		if (ft_putchar('0') == -1)
			return (-1);
		else
			return (1);
	}
	if (nbr > 15)
		len += ft_putadd(nbr / 16, charset);
	if (nbr % 16 >= 10)
		len += ft_putchar(charset[nbr % 16 - 10]);
	else
		len += ft_putchar(nbr % 16 + '0');
	return (len);
}
