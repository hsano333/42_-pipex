/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:16:50 by hsano             #+#    #+#             */
/*   Updated: 2022/08/31 20:24:43 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "common.h"
#include "libft_mem.h"

static size_t	find_conversion(const char *str, t_conversion *convs)
{
	char	*p_convs;
	size_t	i;

	convs->valid = false;
	p_convs = NULL;
	i = 1;
	while (str[i])
	{
		p_convs = ft_strchr(VALID_CONVERSIONS, (int)(str[i++]));
		if (p_convs)
			break ;
	}
	if (!p_convs)
		return (i);
	convs->valid = true;
	return (i);
}

static size_t	check_period(const char *str, size_t str_size)
{
	char	*p;
	size_t	period_index;

	p = ft_memchr(str, '.', str_size);
	if (!p)
		return (str_size - 1);
	period_index = p - str;
	return (period_index);
}

static size_t	where_label_last(const char *str, size_t size)
{
	size_t	i;

	i = 0;
	while (str[i] && i < size)
	{
		if ('1' <= str[i] && str[i] <= '9')
			return (i);
		i++;
	}
	return (i);
}

static void	parse_conversion(const char *str, t_conversion *convs)
{
	size_t	middle_point;
	char	ascii_aray[256];

	ft_memset(convs, 0, sizeof(t_conversion));
	ft_memset(ascii_aray, 0, 256);
	convs->point = str;
	convs->size = find_conversion(str, convs);
	if (convs->valid == false)
		return ;
	middle_point = check_period(str, convs->size);
	convs->mini_width = ft_atoin(str, middle_point, FRONT);
	convs->precision = ft_atoin(&(str[middle_point]), \
			convs->size - middle_point - 1, BACK);
	if (convs->mini_width <= ERROR_ATOI || convs->precision <= ERROR_ATOI)
		return ;
	middle_point = where_label_last(str, middle_point);
	set_ascii(str, middle_point, ascii_aray);
	convs->flag_minus = (ascii_aray['-'] == true);
	convs->flag_plus = (ascii_aray['+'] == true);
	convs->flag_sharp = (ascii_aray['#'] == true);
	convs->flag_space = (ascii_aray[' '] == true);
	convs->flag_zero = (ascii_aray['0'] == true);
	convs->conversion = str[convs->size - 1];
	check_error(str, convs, middle_point, ascii_aray);
}

t_list	*parse_str(const char *str)
{
	const char		*pp;
	t_conversion	*convs;
	t_list			*convs_list;
	t_list			*new_list;
	void			(*del_convs)(void *);

	convs_list = NULL;
	del_convs = (void (*)())clear_conversion;
	pp = ft_strchr(str, '%');
	while (pp)
	{
		convs = (t_conversion *)malloc(sizeof(t_conversion));
		if (!convs)
			break ;
		parse_conversion(pp, convs);
		new_list = ft_lstnew(convs);
		if (!new_list)
			break ;
		ft_lstadd_back(&convs_list, new_list);
		pp = ft_strchr(pp + convs->size, '%');
	}
	if (!convs || !new_list)
		ft_lstclear(&convs_list, del_convs);
	return (convs_list);
}
