/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 22:44:24 by hsano             #+#    #+#             */
/*   Updated: 2022/08/14 03:13:29 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	fix_precision_and_minisize(char *str, t_conversion *convs)
{
	int		str_len;

	if (convs->precision >= 0 || str[0] == '\0' )
		convs->flag_zero = false;
	str_len = (int)ft_strlen(str);
	if (str_len >= convs->precision)
		convs->precision = str_len;
	if (convs->mini_width >= convs->precision)
		convs->mini_width -= convs->precision;
	else
		convs->mini_width = 0;
	if (convs->precision >= str_len)
		convs->precision -= str_len;
	else
		convs->precision = 0;
	if (convs->flag_sharp && convs->mini_width >= 2)
		convs->mini_width -= 2;
	else if (convs->flag_sharp)
		convs->mini_width = 0;
	if (convs->mini_width < 0)
		convs->mini_width = 0;
	if (convs->precision < 0)
		convs->precision = 0;
}

char	*get_str_uint_digit(va_list *args, t_conversion *convs)
{
	unsigned int	word;
	char			*str;

	word = va_arg(*args, unsigned int);
	str = ft_strnbr_base(word, BASE_DIGIT);
	if (!str)
		return (NULL);
	if (convs->precision == ZERO && str[0] == '0')
		str[0] = '\0';
	fix_precision_and_minisize(str, convs);
	convs->mem_err = false;
	convs->free_str = true;
	convs->arg_len = ft_strlen(str);
	return (str);
}

char	*get_str_int_digit(va_list *args, t_conversion *convs)
{
	long long	word;
	char		*str;

	word = va_arg(*args, int);
	if (word < 0)
	{
		word = -1 * word;
		convs->minus_value = true;
	}
	str = ft_strnbr_base(word, BASE_DIGIT);
	if (!str)
		return (NULL);
	if (convs->precision == ZERO && str[0] == '0')
		str[0] = '\0';
	fix_precision_and_minisize(str, convs);
	if ((convs->minus_value || ((convs->flag_plus || convs->flag_space))) \
													&& convs->mini_width > 0)
		convs->mini_width--;
	convs->mem_err = false;
	convs->free_str = true;
	convs->arg_len = ft_strlen(str);
	return (str);
}

char	*get_str_int_hex(va_list *args, t_conversion *convs)
{
	unsigned long long	word;
	char				*str;

	word = (unsigned long long)va_arg(*args, unsigned int);
	convs->sharp_str[0] = '0';
	convs->sharp_str[1] = convs->conversion;
	if (convs->conversion == 'x')
		str = ft_strnbr_base(word, BASE_HEX_LOWER);
	else
		str = ft_strnbr_base(word, BASE_HEX_UPPER);
	if (!str)
		return (NULL);
	if (convs->precision == ZERO)
		convs->flag_zero = false;
	if ((convs->precision == ZERO) && str[0] == '0')
		str[0] = '\0';
	if (str[0] == '\0' || str[0] == '0')
		convs->flag_sharp = false;
	fix_precision_and_minisize(str, convs);
	convs->mem_err = false;
	convs->free_str = true;
	convs->arg_len = ft_strlen(str);
	return (str);
}
