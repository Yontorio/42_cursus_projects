/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:57:43 by ahoummad          #+#    #+#             */
/*   Updated: 2024/12/07 00:25:03 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

struct	s_flags
{
	int	minus;
	int	plus;
	int	hash;
	int	space;
	int	width;
	int	iswidth;
	int	zero;
	int	precision;
	int	isprecision;
	int	sign;
};

int		ft_start(const char *format, va_list args, struct s_flags flag,
			int count);
int		ft_putchar(char c);
int		ft_char(char s, struct s_flags flag);
int		ft_string(const char *format, char *s, struct s_flags flag);
int		ft_integer(int n, struct s_flags flag);
int		ft_numlen(int n);
int		ft_minus_int(int n, struct s_flags flag);
int		ft_calculate_length_int(int n, struct s_flags *flag);
int		ft_process_sign_and_flags(int *n, struct s_flags *flag);
int		ft_recursive_putnbr(int n);
int		ft_putnbr(int n, struct s_flags flag);
int		ft_unsigned(unsigned int n, struct s_flags flag);
int		ft_unsigned_len(unsigned int num);
int		ft_hexa(unsigned int n, int uppercase, struct s_flags flag);
int		ft_hex_len(unsigned int num);
int		ft_calculate_length_hex(unsigned int n, struct s_flags *flag);
int		ft_puthex(unsigned int n, int uppercase, struct s_flags flag);
int		ft_minus_hex(unsigned int n, int uppercase, struct s_flags flag);
int		ft_calculate_total_length(unsigned int n, struct s_flags flag);
int		ft_pointer(void *ptr, struct s_flags flag);
int		ft_pointer_len(void *ptr);
int		ft_puthexptr(unsigned long n, int uppercase, struct s_flags flag);
int		ft_minus_padding(void *ptr, struct s_flags flag);
int		ft_putpointer(void *ptr, struct s_flags flag);
int		ft_printf(const char *format, ...);

#endif
