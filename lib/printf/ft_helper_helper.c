/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 09:22:19 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/27 11:05:07 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr2(int number, int *counter)
{
	if (number == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
		*counter += 11;
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

int	ft_putaddress2(unsigned long number, int *counter)
{
	if (number >= 10)
	{
		(*counter)++;
		if (number >= 16)
			ft_putaddress2(number / 16, counter);
		number = number % 16;
		if (number >= 10)
			number = number + 87;
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
