/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 23:22:52 by hsano             #+#    #+#             */
/*   Updated: 2022/08/06 18:11:12 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst_p;
	unsigned char	*src_p;

	if (len == 0)
		return (dst);
	else if (dst == NULL && src == NULL)
		return (NULL);
	if (src >= dst || src + len <= dst)
		ft_memcpy(dst, src, len);
	else
	{
		i = len;
		dst_p = (unsigned char *)(&(((unsigned char *)dst)[len - 1]));
		src_p = (unsigned char *)(&(((unsigned char *)src)[len - 1]));
		while (i--)
			*(dst_p--) = *(src_p--);
	}
	return (dst);
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
//	char *o1;
//	char *o2;
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
//		printf("my  memmove s1=%s,s2=%s,len=%zu\n",s1,s2,len);
//		o1 = ft_memmove(s1,s2,len);
//		printf("my   result=%s\n",o1);
//		printf("test memmove s3=%s,s4=%s,len=%zu\n",s3,s4,len);
//		o2 = memmove(s3,s4,len);
//		printf("test   result=%s\n",o2);
//		printf("my=%s,test=%s\n",o1,o2);
//
//
//
//	}
//	return (0);
//}
