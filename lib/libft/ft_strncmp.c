/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:46:01 by hsano             #+#    #+#             */
/*   Updated: 2022/07/18 16:54:46 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	if (n == 0)
		return (0);
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	i = 0;
	while (us1[i] && us2[i] && (i < n))
	{
		if (us1[i] != us2[i])
			return ((int)(us1[i] - us2[i]));
		i++;
	}
	if (i == n)
		return (0);
	return ((int)(us1[i] - us2[i]));
}
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//int main(int argc,char **argv)
//{
//	char *s1;
//	char *s2;
//	int 	result;
//	size_t		len;
//
//	printf("test1 \n");
//	//strncmp("hello", NULL, 3);
//	printf("test2 \n");
//	//strncmp(NULL, "hello", 3);
//	printf("test3 \n");
//	strncmp(NULL, NULL, 3);
//
//
//	printf("test1 \n");
//	ft_strncmp("hello", NULL, 0);
//	printf("test2 \n");
//	ft_strncmp(NULL, "hello", 0);
//	printf("test3 \n");
//	ft_strncmp(NULL, NULL, 0);
//
//	if (argc == 4)
//	{
//		s1 = argv[1];
//		s2 = argv[2];
//		if (s1[0] == '\0')
//			s1 = NULL;
//		if (s2[0] == '\0')
//			s2 = NULL;
//		len = atoi(argv[3]);
//		result = ft_strncmp(s1,s2,len);
//		printf("s1=%s,s2=%s,len=%zu\n",s1,s2,len);
//		printf("result=%d\n",result);
//		result = strncmp(s1,s2,len);
//		printf("result=%d\n",result);
//
//	}
//	else if (argc == 5)
//	{
//		s1 = argv[1];
//		s2 = argv[2];
//		if (s1[0] == '\0')
//			s1 = NULL;
//		if (s2[0] == '\0')
//			s2 = NULL;
//		len = atoi(argv[3]);
//
//		printf("s1=%s,s2=%s,len=%zu\n",s1,s2,len);
//		if (argv[4][0] == '1')
//		{
//			result = ft_strncmp(s1,s2,len);
//			printf("result=%d\n",result);
//		}
//		else
//		{
//			result = strncmp(s1,s2,len);
//			printf("result=%d\n",result);
//
//		}
//
//	}
//	return (0);
//}
