/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:40:30 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/27 10:38:00 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		ft_whats_to_print(char format, va_list args, int *counter);
int		ft_printchr(va_list args, int *counter);
int		ft_printstr(va_list args, int *counter);
int		ft_printint(va_list args, char format, int *counter);
int		ft_putnbr(int number, int *counter);
int		ft_hexa(unsigned int number, int *counter, char format);
int		ft_printunint(va_list args, int *counter);
int		ft_putunint(unsigned int number, int *counter);
int		ft_printvoid(va_list args, int *counter);
int		ft_putaddress(void *address, int *counter);
int		ft_putaddress2(unsigned long number, int *counter);
int		ft_putnbr2(int number, int *counter);

#endif