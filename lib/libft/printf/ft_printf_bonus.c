/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:16:50 by hsano             #+#    #+#             */
/*   Updated: 2022/08/12 00:41:32 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "parse.h"

int	ft_printf(const char *str, ...)
{
	int		print_size;
	t_list	*c_list;
	va_list	args;

	c_list = parse_str(str);
	va_start(args, str);
	print_size = print(str, c_list, &args);
	va_end(args);
	return (print_size);
}
