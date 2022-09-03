/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:26:36 by hsano             #+#    #+#             */
/*   Updated: 2022/08/09 15:13:08 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	tmp;

	i = 0;
	p = (unsigned char *)s;
	tmp = (unsigned char)c;
	while (i < n)
	{
		if (*(p++) == tmp)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//int main(int argc, char **argv)
//{
//	char	test[] = {1,2,3,4,5,6,7,8,9,0,11,12,13,14};
//	char *test2;
//	char *p;
//	char *q;
//	int	len;
//
//	len = 5;
//	if (argc == 2)
//		len = atoi(argv[1]);
//	test2 = &(test[0]);
//	if (argc == 3)
//	{
//		test2 = argv[2];
//		if (argv[2][0] == '\0')
//			test2 = NULL;
//	}
//	p = ft_memchr("NULL",3,len);
//	q = memchr("NULL",3,100);
//	printf("my:%p\n",p);
//	printf("test:%p\n",q);
//
//	p = ft_memchr(test,20,len);
//	q = memchr(test,20,len);
//	printf("my:%p\n",q);
//	printf("test:%p\n",p);
//	return (0);
//}
