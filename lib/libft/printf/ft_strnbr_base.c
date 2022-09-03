/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 09:34:44 by hsano             #+#    #+#             */
/*   Updated: 2022/08/11 01:23:16 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include <libft_str.h>
#include <stdint.h>

#define ZERO_STR "0"
#define LLMIN_STR "-922337203685477580"

static char	*put_base(unsigned long long nbr, char *base, unsigned int count,
		int minus)
{
	int		i;
	int		tmp_i;
	char	array[100];
	char	*swap;

	i = 0;
	while (nbr != 0)
	{
		array[i++] = base[nbr % count];
		nbr = nbr / count;
	}
	if (minus == -1)
		array[i++] = '-';
	swap = malloc(i + 1);
	if (!swap)
		return (NULL);
	swap[i] = '\0';
	i--;
	tmp_i = 0;
	while (tmp_i <= i)
	{
		swap[i - tmp_i] = array[tmp_i];
		tmp_i++;
	}
	return (swap);
}

static unsigned int	check_base(char *base)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (false);
		j = 0;
		while (base[j])
		{
			if ((i != j) && (base[i] == base[j]))
				return (false);
			j++;
		}
		i++;
	}
	if (i <= 1)
		return (false);
	return (i);
}

static char	*check_min(long long nbr, int *minus, int *err)
{
	char	*p;

	*err = false;
	if (nbr == LLONG_MIN || nbr == 0)
	{
		if (nbr == LLONG_MIN)
			p = malloc(20);
		else
			p = malloc(2);
		if (!p)
		{
			*err = true;
			return (NULL);
		}
		if (nbr == LLONG_MIN)
			ft_strlcpy(p, &LLMIN_STR[0], 20);
		else
			ft_strlcpy(p, &ZERO_STR[0], 2);
		return (p);
	}
	*minus = 1;
	if (nbr < 0)
		*minus = -1;
	return (NULL);
}

char	*ft_strnbr_base(long long nbr, char *base)
{
	int					minus;
	int					err;
	char				*p;
	unsigned long long	nbrl;
	unsigned int		count;

	p = check_min(nbr, &minus, &err);
	if (p != NULL || err == true)
		return (p);
	nbrl = minus * nbr;
	count = check_base(base);
	if (count == false)
		return (NULL);
	if (count > 1)
		return (put_base((unsigned long long)nbrl, base, count, minus));
	return (NULL);
}

char	*ft_strpointer_base(uintptr_t nbrl, char *base)
{
	unsigned int	count;
	int				minus;
	char			*p;

	minus = 1;
	if (nbrl == 0)
	{
		p = malloc(2);
		if (!p)
			return (NULL);
		ft_strlcpy(p, &ZERO_STR[0], 2);
		return (p);
	}
	count = check_base(base);
	if (count == false)
		return (NULL);
	if (count > 1)
		return (put_base(nbrl, base, count, minus));
	return (NULL);
}
//#include <stdlib.h>
//#include <stdio.h>
//int main(int argc , char **argv)
//{
//	char *str;
//	char *str2;
//	if (argc == 3)
//	{
//		str = argv[1];
//		str2 = argv[2];
//		ft_putnbr_base(atoi(str),str2);
//		printf("atol:[%d]\n",atoi(str));
//	}
//}
