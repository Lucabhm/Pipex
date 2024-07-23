/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:40:35 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/27 11:04:40 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int number, int *counter)
{
	if (number < 0 && number != -2147483648)
	{
		(*counter)++;
		if (write(1, "-", 1) == -1)
			return (-1);
		if (ft_putnbr(-number, counter) == -1)
			return (-1);
	}
	else if (number >= 10)
	{
		(*counter)++;
		if (ft_putnbr(number / 10, counter) == -1)
			return (-1);
		number = number % 10 + '0';
		if (write(1, &number, 1) == -1)
			return (-1);
	}
	else
		if (ft_putnbr2(number, counter) == -1)
			return (-1);
	return (0);
}

int	ft_hexa(unsigned int number, int *counter, char format)
{
	if (number >= 10)
	{
		(*counter)++;
		if (number >= 16)
			if (ft_hexa(number / 16, counter, format) == -1)
				return (-1);
		number = number % 16;
		if (number >= 10 && format == 'x')
			number = number + 87;
		else if (number >= 10 && format == 'X')
			number = number + 55;
		else
			number = number + '0';
		if (write(1, &number, 1) == -1)
			return (-1);
	}
	else
	{
		(*counter)++;
		number = number + '0';
		if (write(1, &number, 1) == -1)
			return (-1);
	}
	return (0);
}

int	ft_putunint(unsigned int number, int *counter)
{
	if (number >= 10)
	{
		(*counter)++;
		if (ft_putunint(number / 10, counter) == -1)
			return (-1);
		number = number % 10 + '0';
		if (write(1, &number, 1) == -1)
			return (-1);
	}
	else
	{
		(*counter)++;
		number = number + '0';
		if (write(1, &number, 1) == -1)
			return (-1);
	}
	return (0);
}

int	ft_putaddress(void *address, int *counter)
{
	unsigned long	cpyaddress;

	cpyaddress = (unsigned long)address;
	if (ft_putaddress2(cpyaddress, counter) == -1)
		return (-1);
	return (0);
}
