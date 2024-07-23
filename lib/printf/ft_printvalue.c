/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printvalue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:52:41 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/27 09:13:51 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchr(va_list args, int *counter)
{
	char	letter;

	letter = va_arg(args, int);
	if (write(1, &letter, 1) == -1)
		return (-1);
	(*counter)++;
	return (0);
}

int	ft_printstr(va_list args, int *counter)
{
	char	*str;
	int		i;

	i = 0;
	str = va_arg(args, char *);
	if (str == NULL)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		*counter += 6;
		return (0);
	}
	while (str[i] != '\0')
	{
		if (write (1, &str[i], 1) == -1)
			return (-1);
		i++;
		(*counter)++;
	}
	return (0);
}

int	ft_printint(va_list args, char format, int *counter)
{
	int	digit;

	if (format == 'i' || format == 'd')
	{
		digit = va_arg(args, int);
		if (ft_putnbr(digit, counter) == -1)
			return (-1);
	}
	else if (format == 'x' || format == 'X')
	{
		digit = va_arg(args, unsigned int);
		if (ft_hexa(digit, counter, format) == -1)
			return (-1);
	}
	return (0);
}

int	ft_printunint(va_list args, int *counter)
{
	unsigned int	digit;

	digit = va_arg(args, unsigned int);
	if (ft_putunint(digit, counter) == -1)
		return (-1);
	return (0);
}

int	ft_printvoid(va_list args, int *counter)
{
	void	*address;

	address = va_arg(args, void *);
	if (write(1, "0x", 2) == -1)
		return (-1);
	*counter += 2;
	if (ft_putaddress(address, counter) == -1)
		return (-1);
	return (0);
}
