/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcus <marcus@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:54:24 by hleung            #+#    #+#             */
/*   Updated: 2023/02/19 20:08:09 by marcus           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(int n, char *charset)
{
	int				len;
	unsigned int	nbr;

	len = 0;
	nbr = n;
	if (nbr == 0)
	{
		ft_putchar('0');
		return (1);
	}
	if (n < 0)
		nbr = 4294967296 + n;
	if (nbr > 15)
		len += ft_putnbr_base(nbr / 16, charset);
	if (nbr % 16 >= 10)
		len += ft_putchar(charset[nbr % 16 - 10]);
	else
		len += ft_putchar(nbr % 16 + '0');
	return (len);
}
