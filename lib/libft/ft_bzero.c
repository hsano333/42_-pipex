/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 23:01:53 by hsano             #+#    #+#             */
/*   Updated: 2022/07/16 13:51:10 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = n / (sizeof(unsigned long long) / sizeof(char));
	if (i > 0)
	{
		while (i--)
			((unsigned long long *)s)[i] = 0;
	}
	i = sizeof(unsigned long long);
	if (n >= i)
	{
		while (--i)
			((char *)s)[n - i] = 0;
	}
	else
	{
		while (n--)
			((char *)s)[n] = 0;
	}
}
//#include <string.h>
//int main(int argc, char **argv)
//{
//	char test1[128];
//	char test2[128];
//
//	if (argc == 2)
//	{
//		printf("s=%s\n",argv[1]);
//		ft_bzero(test1, (atoi(argv[1])));
//		printf("my	 =%s\n",test1);
//		bzero(test2, (atoi(argv[1])));
//		printf("test =%s\n",test2);
//	}
//	else if (argc == 3)
//	{
//		if (argv[2][0] == '1')
//		{
//			ft_bzero(test1, (atoi(argv[1])));
//			printf("my	 =%s\n",test1);
//			ft_bzero(NULL, (atoi(argv[1])));
//			printf("my	 =%s\n",test1);
//		}
//		else
//		{
//			bzero(test2, (atoi(argv[1])));
//			printf("test =%s\n",test2);
//			bzero(NULL, (atoi(argv[1])));
//			printf("test =%s\n",test2);
//
//		}
//	}
//}
