/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 00:57:37 by hsano             #+#    #+#             */
/*   Updated: 2022/08/01 02:47:13 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	while (i < dstsize - 1 && *src)
	{
		*(dst++) = *(src++);
		i++;
	}
	*dst = '\0';
	return (len);
}
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//int main(int argc,char **argv)
//{
//	char *s1;
//	char *s2;
//	char *s3;
//	char *s4;
//	size_t o1;
//	size_t o2;
//	size_t		len;
//	if (argc == 6)
//	{
//		s1 = argv[1];
//		s2 = argv[2];
//		s3 = argv[3];
//		s4 = argv[4];
//		if (s1[0] == '\0')
//			s1 = NULL;
//		if (s2[0] == '\0')
//			s2 = NULL;
//		if (s3[0] == '\0')
//			s3 = NULL;
//		if (s4[0] == '\0')
//			s4 = NULL;
//		len = atoi(argv[5]);
//		printf("my   s1=%s,s2=%s,len=%zu\n",s1,s2,len);
//		o1 = ft_strlcpy(s1,s2,len);
//		printf("my   strlcpy s1=%s,result=%zu\n",s1,o1);
//		printf("test s3=%s,s4=%s,len=%zu\n",s3,s4,len);
//		o2 = strlcpy(s3,s4,len);
//		printf("test strlcpy s3=%s,result=%zu\n",s3,o2);
//		printf("my=%zu,test=%zu\n",o1,o2);
//
//
//	}
//	return (0);
//}
