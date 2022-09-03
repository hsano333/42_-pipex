/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 02:50:00 by hsano             #+#    #+#             */
/*   Updated: 2022/07/16 23:16:31 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*p;
	char	*bk;

	size = ft_strlen(s1);
	p = (char *)malloc(size + 1);
	bk = p;
	if (p == NULL)
		return (NULL);
	p[size] = '\0';
	while (size--)
		*(p++) = *(s1++);
	return (bk);
}
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//int main(int argc,char **argv)
//{
//	char *s1;
//	char *s2;
//	char *s3;
//	if (argc == 2)
//	{
//		s1 = argv[1];
//		if (s1[0] == '\0')
//			s1 = NULL;
//		s2 = ft_strdup(s1);
//		s3 = strdup(s1);
//		printf("s1=%s,my=%s,test=%s\n",s1,s2,s3);
//		free(s2);
//		free(s3);
//
//	}
//	return (0);
//}
