/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 07:10:36 by hsano             #+#    #+#             */
/*   Updated: 2022/09/01 20:50:36 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_common.h"

static	size_t	calc(const char *str, size_t i, size_t len, int *long_over_flag)
{
	size_t	a;
	size_t	sum;

	sum = 0;
	*long_over_flag = true;
	a = ft_iterative_power(10, len - 1);
	if (a == LONG_MAX || (LONG_MAX / a < (size_t)(str[i] - '0')))
		return (0);
	while (a > 0)
	{
		sum += (str[i++] - '0') * a;
		if (sum < (str[i - 1] - '0') * a || sum > LONG_MAX + 1UL)
			return (0);
		a /= 10;
	}
	*long_over_flag = false;
	return (sum);
}

long	ft_atol(const char *str, int *long_over_flag)
{
	int		minus;
	size_t	len;
	size_t	i;
	size_t	sum;

	*long_over_flag = true;
	i = remove_zero(str, get_start_index(str, &minus));
	len = get_digit_len(str, i);
	if (len == 0)
	{
		if (str && ((i > 0 && str[i - 1] == '0') || (i == 0 && str[i] == '0')))
			*long_over_flag = false;
		return (0);
	}
	sum = calc(str, i, len, long_over_flag);
	if (minus == 1 && sum == LONG_MAX + 1UL)
		return (0);
	return ((long)(sum * minus));
}
