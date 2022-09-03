/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 20:03:06 by hsano             #+#    #+#             */
/*   Updated: 2022/09/01 20:43:35 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_count(char *p, long n)
{
	long long	a;
	size_t		i;	
	size_t		cnt;

	i = 0;
	cnt = 0;
	if (n < 0)
	{
		a = -1 * (long long)n;
		cnt++;
	}
	else
		a = n;
	while (a)
	{
		p[i++] = (a % 10) + '0';
		a /= 10;
		cnt++;
	}
	if (n < 0)
		p[i++] = '-';
	return (cnt);
}

static void	ft_itoa_no_memory(long n, char *p, char *r)
{
	size_t	i;
	size_t	cnt;

	if (n == 0)
	{
		r[0] = '0';
		r[1] = '\0';
		return ;
	}
	else if (n == LONG_MIN)
	{
		ft_strlcpy(r, "-9223372036854775808", 21);
		return ;
	}
	cnt = get_count(p, n);
	r[cnt] = '\0';
	i = 0;
	while (i < cnt)
	{
		r[i] = p[cnt - i - 1];
		i++;
	}
}

char	*ft_ltoa(long n, char *r)
{
	char	p[30];

	ft_itoa_no_memory(n, p, &(r[0]));
	return (r);
}
//#include <stdlib.h>
//int main(int argc, char **argv)
//{
//	char tmp[100];
//	long c;
//	int	fd;
//	if (argc == 2)
//	{
//		c = atol(argv[1]);
//		ft_ltoa(c, tmp);
//		printf("c=%ld, result=%s\n", c, tmp);
//		//fd = atoi(argv[2]);
//		//ft_putnbr_fd(c, fd);
//	}
//}
