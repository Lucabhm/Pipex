/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:18:42 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/27 10:43:47 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_whats_to_print(char format, va_list args, int *counter);

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			if (ft_whats_to_print(format[i], args, &counter) == -1)
				return (-1);
		}
		else
		{
			if (write(1, &format[i], 1) == -1)
				return (-1);
			counter++;
		}
		i++;
	}
	va_end(args);
	return (counter);
}

int	ft_whats_to_print(char format, va_list args, int *counter)
{
	int	error;

	error = 0;
	if (format == 'c')
		error = ft_printchr(args, counter);
	if (format == 's')
		error = ft_printstr(args, counter);
	if (format == 'i' || format == 'd'
		|| format == 'x' || format == 'X')
		error = ft_printint(args, format, counter);
	if (format == 'p')
		error = ft_printvoid(args, counter);
	if (format == 'u')
		error = ft_printunint(args, counter);
	if (format == '%')
	{
		if (write(1, "%", 1) == -1)
			return (-1);
		(*counter)++;
	}
	return (error);
}
