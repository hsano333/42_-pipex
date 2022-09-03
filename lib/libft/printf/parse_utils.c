/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:25:55 by hsano             #+#    #+#             */
/*   Updated: 2022/08/11 14:14:40 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "common.h"

int	is_invalid_int_numbers(const char **str, size_t size, int mode)
{
	size_t	i;
	size_t	first_digit;

	if (mode == FRONT)
	{
		i = 0;
		while (!('1' <= (*str)[i] && (*str)[i] <= '9') && i < size)
			i++;
		first_digit = i;
		while (('0' <= (*str)[i] && (*str)[i] <= '9') && i < size)
			i++;
		if (i - first_digit >= 11)
			return (true);
	}
	else
	{
		i = size - 1;
		while (('0' <= (*str)[i] && (*str)[i] <= '9') && i > 0)
			i--;
		if (size - i >= 11)
			return (true);
		first_digit = ++i;
	}
	*str = &((*str)[first_digit]);
	return (false);
}

int	ft_atoin(const char *str, size_t size, int mode)
{
	char	*p;
	int		tmp_int;
	int		tmp_error;

	if (size == 0 && mode == BACK)
		return (NONE);
	else if (size == 1 && mode == BACK)
		return (ZERO);
	tmp_error = is_invalid_int_numbers(&str, size, mode);
	if (tmp_error)
		return (OVERFLOW);
	p = ft_substr(str, 0, size);
	if (!p)
		return (MEMORY_ERROR);
	tmp_int = ft_atoi_base(p, BASE_DIGIT, &tmp_error);
	free(p);
	if (tmp_error)
		return (OVERFLOW);
	return (tmp_int);
}

void	set_ascii(const char *str, size_t middle_point, char *ascii_aray)
{
	size_t	i;

	i = 0;
	while (i < middle_point)
		ascii_aray[(int)str[i++]] = true;
}

void	check_error(const char *str, t_conversion *convs, \
						size_t middle_point, char *ascii_aray)
{
	int		sum;
	char	*p;
	size_t	i;

	i = 0;
	sum = 0;
	convs->valid = false;
	ascii_aray['-'] = false;
	ascii_aray['+'] = false;
	ascii_aray['#'] = false;
	ascii_aray['0'] = false;
	ascii_aray[' '] = false;
	ascii_aray['%'] = false;
	while (i < 256)
		sum += ascii_aray[i++];
	if (sum > 0)
		return ;
	i = middle_point;
	while (i < convs->size - 1)
	{
		p = ft_strchr("0123456789.", (int)(str[i++]));
		if (!p)
			return ;
	}
	convs->valid = true;
}
//#include <stdio.h>
//void	info_conversion(t_conversion *convs)
//{
//	printf("\ninfo:convs->point:[%s]\n", convs->point);
//	printf("convs->size:%zu\n", convs->size);
//	printf("convs->conversion:%c\n", convs->conversion);
//	printf("convs->mini_width:%d\n", convs->mini_width);
//	printf("convs->precision:%d\n", convs->precision);
//	printf("convs->flag_minus:%d\n", convs->flag_minus);
//	printf("convs->flag_plus:%d\n", convs->flag_plus);
//	printf("convs->flag_sharp:%d\n", convs->flag_sharp);
//	printf("convs->flag_space:%d\n", convs->flag_space);
//	printf("convs->flag_zero:%d\n", convs->flag_zero);
//	printf("convs->valid:%d\n", convs->valid);
//	printf("convs->mem_err:%d\n", convs->mem_err);
//	printf("convs->minus_value:%d\n", convs->minus_value);
//	printf("convs->print_size:%zu\n", convs->print_size);
//}
