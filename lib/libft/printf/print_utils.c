/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:11:22 by hsano             #+#    #+#             */
/*   Updated: 2022/08/14 03:13:51 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

size_t	put_flag_minus(t_conversion *convs, char *str, char padding)
{
	size_t	print_size;

	print_size = 0;
	if (convs->minus_value)
		print_size += write(1, "-", 1);
	else if (convs->flag_plus)
		print_size += write(1, "+", 1);
	else if (convs->flag_space)
		print_size += write(1, " ", 1);
	if (convs->flag_sharp)
		print_size += write(1, &convs->sharp_str, 2);
	while (convs->precision--)
		print_size += write(1, "0", 1);
	print_size += write(1, str, convs->arg_len);
	while (convs->mini_width--)
		print_size += write(1, &padding, 1);
	return (print_size);
}

size_t	put_except_minus(t_conversion *convs, char *str, char padding)
{
	size_t	print_size;

	print_size = 0;
	while (padding == ' ' && (convs->minus_value || convs->flag_plus) \
							&& convs->mini_width--)
		print_size += write(1, &padding, 1);
	if (convs->minus_value)
		print_size += write(1, "-", 1);
	else if (convs->flag_plus)
		print_size += write(1, "+", 1);
	else if (convs->flag_space)
		print_size += write(1, " ", 1);
	while (convs->mini_width > 0 && convs->mini_width--)
		print_size += write(1, &padding, 1);
	if (convs->flag_sharp)
		print_size += write(1, &convs->sharp_str, 2);
	while (convs->precision--)
		print_size += write(1, "0", 1);
	print_size += write(1, str, convs->arg_len);
	return (print_size);
}

size_t	is_sign(t_conversion *convs, char *str)
{
	if (convs->minus_value)
		return (1);
	else if (convs->flag_plus && ft_isdigit(str[0]))
		return (1);
	else if (convs->flag_space && ft_isdigit(str[0]))
		return (1);
	return (0);
}

size_t	get_estimated_size(t_conversion *convs, char *str)
{
	size_t	len;

	len = convs->arg_len;
	if (convs->flag_sharp)
		len += 2;
	if (convs->minus_value)
		len++;
	else if ((convs->flag_plus || convs->flag_space) && ft_isdigit(str[0]))
		len++;
	len += convs->mini_width;
	len += convs->precision;
	return (len);
}

size_t	ft_putstr_fd_wrapper(char *str, int fd, ssize_t *print_size)
{
	size_t	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	ft_putstr_fd(str, fd);
	if (*print_size == PRINT_SIZE_OVER || len >= INT_MAX \
			|| *print_size >= INT_MAX - (int)len)
		*print_size = PRINT_SIZE_OVER;
	else
		*print_size += len;
	return (len);
}
