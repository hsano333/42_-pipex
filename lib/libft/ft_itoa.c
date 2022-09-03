/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:12:09 by hsano             #+#    #+#             */
/*   Updated: 2022/07/15 00:10:53 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_count(char *p, int n)
{
	long	a;
	size_t	i;	
	size_t	cnt;

	i = 0;
	cnt = 0;
	if (n < 0)
	{
		a = -1 * (long)n;
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

static char	*str_zero(void)
{
	char	*p;

	p = malloc(2);
	if (!p)
		return (NULL);
	p[0] = '0';
	p[1] = '\0';
	return (p);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	p[20];
	char	*r;
	size_t	cnt;

	if (n == 0)
		return (str_zero());
	cnt = get_count(p, n);
	r = malloc(cnt + 1);
	if (!r)
		return (NULL);
	r[cnt] = '\0';
	i = 0;
	while (i < cnt)
	{
		r[i] = p[cnt - i - 1];
		i++;
	}
	return (r);
}
//int main(int argc, char **argv)
//{
//	char *p;
//
//	if (argc == 2)
//	{
//		p = ft_itoa(ft_atoi(argv[1]));
//		printf("p = %s\n",p);
//	}
//}
