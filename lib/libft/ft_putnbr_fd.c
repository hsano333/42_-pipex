/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:51:46 by hsano             #+#    #+#             */
/*   Updated: 2022/08/25 20:02:25 by hsano            ###   ########.fr       */
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

static void	ft_itoa_no_memory(int n, char *p, char *r)
{
	size_t	i;
	size_t	cnt;

	if (n == 0)
	{
		r[0] = '0';
		r[1] = '\0';
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

void	ft_putnbr_fd(int n, int fd)
{
	char	p[20];
	char	r[20];

	ft_itoa_no_memory(n, &(p[0]), &(r[0]));
	ft_putstr_fd(r, fd);
}
//#include <stdlib.h>
//int main(int argc, char **argv)
//{
//	int c;
//	int	fd;
//	if (argc == 3)
//	{
//		c = atoi(argv[1]);
//		fd = atoi(argv[2]);
//		ft_putnbr_fd(c, fd);
//	}
//}
