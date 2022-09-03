/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:37:16 by hsano             #+#    #+#             */
/*   Updated: 2022/07/18 16:58:25 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*process(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;
	size_t	len_n;

	i = -1;
	k = 0;
	len_n = ft_strlen(needle);
	if (len_n == 0)
		return ((char *)haystack);
	if (len_n > ft_strlen(haystack) || len_n > len)
		return (NULL);
	while (++i < len)
	{
		if (haystack[i] == needle[k])
			k++;
		else
		{
			i -= k;
			k = 0;
		}
		if (len_n == k)
			return (&(((char *)haystack)[i - len_n + 1]));
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (len == 0)
	{
		if (needle == NULL || needle[0] == '\0')
			return ((char *)haystack);
		return (NULL);
	}
	return (process(haystack, needle, len));
}
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//int main(int argc,char **argv)
//{
//	char *s1;
//	char *s2;
//	char *result;
//	size_t		len;
//	printf("test start\n");
//	result = strnstr("oh no not the empty string !", "", 0);
//	printf("origin result=%s\n",result);
//	result = ft_strnstr("oh no not the empty string !", "", 0);
//	printf("my result=%s\n",result);
//
//	printf("test2 start\n");
//	result = strnstr("oh no not the empty string !", "z", 0);
//	printf("origin result=%s\n",result);
//	result = ft_strnstr("oh no not the empty string !", "z", 0);
//	printf("my result=%s\n",result);
//
//	if (argc == 4)
//	{
//		s1 = argv[1];
//		s2 = argv[2];
//		len = atoi(argv[3]);
//		result = ft_strnstr(s1,s2,len);
//		printf("s1=%s,s2=%s,len=%zu\n",s1,s2,len);
//		result = strnstr(s1,s2,len);
//		printf("my=  %s\n",result);
//		printf("test=%s\n",result);
//
//	}
//	return (0);
//}
