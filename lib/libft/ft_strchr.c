/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 12:37:44 by hsano             #+#    #+#             */
/*   Updated: 2022/07/16 18:56:57 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	tmp;

	tmp = (char)c;
	while (*s)
	{
		if (*s == tmp)
			return ((char *)s);
		s++;
	}
	if (tmp == '\0')
		return ((char *)s);
	return (NULL);
}
//#include <stdio.h>
//#include <string.h>
//int main(void)
//{
//	char test[] = "t1est12345";
//	char *p;
//	char *q;
//
//	p = ft_strchr(NULL,'1');
//	q = strchr("NULL",'1');
//	printf("%s\n",p);
//	printf("%s\n",q);
//
//	p = ft_strchr(test,0);
//	q = strchr(test,0);
//	printf("%s\n",q);
//	printf("%s\n",p);
//	return (0);
//}
