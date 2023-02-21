/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcus <marcus@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:47:46 by hleung            #+#    #+#             */
/*   Updated: 2023/02/19 20:24:12 by marcus           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_format(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_print_format(va_list ptr, char format)
{
	int		len;
	char	*low16;

	low16 = "abcdef";
	len = 0;
	if (format == 'c')
		return (len = ft_putchar((unsigned char)va_arg(ptr, int)));
	else if (format == 's')
		return (len = ft_putstr(va_arg(ptr, char *)));
	else if (format == 'd' || format == 'i')
		return (len = ft_putnbr(va_arg(ptr, int)));
	else if (format == 'p')
	{
		ft_putstr("0x");
		return (len = ft_putadd((unsigned long)va_arg(ptr, void *), low16) + 2);
	}
	else if (format == 'u')
		return (len = ft_putnbr_unsigned(va_arg(ptr, unsigned int)));
	else if (format == 'x')
		return (len = ft_putnbr_base(va_arg(ptr, int), low16));
	else if (format == 'X')
		return (len = ft_putnbr_base(va_arg(ptr, int), "ABCDEF"));
	else if (format == '%')
		return (len = ft_putchar('%'));
	return (len);
}

int	ft_printf(const char *arg, ...)
{
	int		i;
	int		len;
	va_list	ptr;

	len = 0;
	i = 0;
	va_start(ptr, arg);
	if (write(1, 0, 0) == -1)
		return (-1);
	while (arg[i])
	{
		if (arg[i] == '%' && ft_check_format(arg[i + 1], "csdipuxX%%"))
		{
			len += ft_print_format(ptr, arg[i + 1]);
			i++;
		}
		else
			len += ft_putchar(arg[i]);
		i++;
	}
	va_end(ptr);
	return (len);
}
