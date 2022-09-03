/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:07:54 by hsano             #+#    #+#             */
/*   Updated: 2022/07/18 16:23:22 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_d;
	size_t	len_s;
	char	*p;

	if (dstsize == 0)
	{
		if (src == NULL)
			return (0);
		return (dstsize + ft_strlen(src));
	}
	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	if (len_d >= dstsize)
		return (len_s + dstsize);
	p = &(dst[len_d]);
	ft_strlcpy(p, src, dstsize - len_d);
	return (len_d + len_s);
}
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//int main(int argc,char **argv)
//{
//	char s1[100] = {1};
//	char *s2;
//	char s3[100] = {1};
//	char *s4;
//	size_t o1;
//	size_t o2;
//	size_t		len;
//
//	//char *dst1 = calloc(100, sizeof(char));
//	//char *dst2 = calloc(100, sizeof(char));
//	char *src1 = calloc(100, sizeof(char));
//	char *src2 = calloc(100, sizeof(char));
//	for (int i = 0; i < 99; i++)
//	{
//		src1[i] = i + 1;
//		src2[i] = i + 1;
//	}
//	/*
//	printf("test start No.1\n");
//	len = ft_strlcat(NULL, "", 0);
//	printf("test start No.2\n");
//	printf("test result=%zu\n",len);
//	len = ft_strlcat(dst1, "", 100);
//	printf("test result=%zu\n",len);
//	*/
//	len = strlcat(NULL, src1, 0);
//	printf("test result=%zu\n",len);
//	len = ft_strlcat(NULL, src1, 0);
//	printf("test result=%zu\n",len);
//
//	/*
//	printf("test start No.4\n");
//	len = strlcat(NULL, "", 0);
//	printf("test result=%zu\n",len);
//	printf("test start No.5\n");
//	len = strlcat(dst2, "", 100);
//	printf("test result=%zu\n",len);
//	*/
//	printf("test start No.6\n");
//	len = strlcat(NULL, src1, 0);
//	printf("test result=%zu\n",len);
//	if (argc == 6)
//	{
//		s2 = argv[2];
//		s4 = argv[4];
//		if (s1[0] == '\0')
//			(s1[0]) = 0;
//		else
//			ft_strlcpy(s1,argv[1], strlen(argv[1]));
//		if (s2[0] == '\0')
//			s2 = NULL;
//		if (s3[0] == '\0')
//			(s3[0]) = 0;
//		else
//			strlcpy(s3,argv[3], strlen(argv[3]));
//		printf("s3=%s, argv=%s,len=%zu\n",s3, argv[3],strlen(argv[3]));
//		if (s4[0] == '\0')
//			s4 = NULL;
//		len = atoi(argv[5]);
//		printf("my   s1=%s,s2=%s,len=%zu\n",s1,s2,len);
//		o1 = ft_strlcat(s1,s2,len);
//		printf("my   strlcat s1=%s,result=%zu\n",s1,o1);
//		printf("test   s3=%s,s4=%s,len=%zu\n",s3,s4,len);
//		o2 = 1;
//		o2 = strlcat(s3,s4,len);
//		printf("test strlcat s3=%s,result=%zu\n",s3,o2);
//		printf("my=%zu,test=%zu\n",o1,o2);
//
//	}
//	return (0);
//}
