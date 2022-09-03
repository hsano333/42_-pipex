/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 21:02:21 by hsano             #+#    #+#             */
/*   Updated: 2022/08/14 03:20:34 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

char	*get_str_char(va_list *args, t_conversion *convs)
{
	int		word_input;
	char	*p;

	convs->precision = 0;
	word_input = (char)va_arg(*args, int);
	p = malloc(2);
	if (!p)
		return (NULL);
	p[0] = word_input;
	p[1] = '\0';
	convs->mem_err = false;
	convs->arg_len = 1;
	convs->free_str = true;
	if (convs->mini_width > 0)
		convs->mini_width -= 1;
	else
		convs->mini_width = 0;
	return (p);
}

char	*get_str_str(va_list *args, t_conversion *convs)
{
	char	*str;
	size_t	len;

	len = 0;
	str = va_arg(*args, char *);
	convs->free_str = false;
	if (str == NULL)
	{
		convs->free_str = true;
		str = ft_strdup(NULL_STR);
		if (!str)
			return (NULL);
	}
	len = ft_strlen(str);
	if (convs->precision == NONE || (size_t)convs->precision > len)
		convs->arg_len = len;
	else if (convs->precision >= 0)
		convs->arg_len = convs->precision;
	convs->precision = 0;
	if (convs->mini_width > 0 && convs->mini_width > (int)convs->arg_len)
		convs->mini_width -= ((int)convs->arg_len);
	else
		convs->mini_width = 0;
	convs->mem_err = false;
	return (str);
}

char	*get_str_percent(va_list *args, t_conversion *convs)
{
	char	*str;

	if (!args)
		return (NULL);
	str = ft_strdup("%");
	if (!str)
		return (NULL);
	convs->precision = 0;
	convs->mini_width = 0;
	convs->mem_err = false;
	convs->free_str = true;
	convs->arg_len = ft_strlen(str);
	return (str);
}

char	*get_str_point(va_list *args, t_conversion *convs)
{
	uintptr_t			word;
	char				*str;

	word = (uintptr_t)va_arg(*args, char *);
	str = ft_strpointer_base(word, BASE_HEX_LOWER);
	if (!str)
		return (NULL);
	if (convs->precision == ZERO && str[0] == '0')
		str[0] = '\0';
	convs->sharp_str[0] = '0';
	convs->sharp_str[1] = 'x';
	convs->mem_err = false;
	convs->free_str = true;
	convs->flag_zero = false;
	convs->arg_len = ft_strlen(str);
	fix_precision_and_minisize(str, convs);
	return (str);
}
