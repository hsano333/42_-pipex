/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 12:55:56 by hsano             #+#    #+#             */
/*   Updated: 2022/07/16 19:20:26 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		cc;
	const char	*head;

	head = s;
	s += ft_strlen(s) + 1;
	cc = (char)c;
	while (s-- != head)
	{
		if (*s == cc)
			return ((char *)s);
	}
	return (0);
}
//#include <stdio.h>
//#include <string.h>
//int main(void)
//{
//	//char test[] = "t1est12345";
//	char test[] = "abcdefg";
//	char *p;
//	char *q;
//
//	p = ft_strrchr(NULL,'a');
//	q = strrchr(NULL,'a');
//	printf("%s\n",p);
//	printf("%s\n",q);
//
//	p = ft_strrchr(test,'g');
//	q = strrchr(test,'g');
//	printf("%s\n",p);
//	printf("%s\n",q);
//	return (0);
//}
