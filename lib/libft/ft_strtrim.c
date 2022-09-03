/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:36:03 by hsano             #+#    #+#             */
/*   Updated: 2022/07/17 20:29:17 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (true);
		i++;
	}
	return (false);
}

void	get_p(const char *s1, const char *set, size_t *begin, size_t *last)
{
	*begin = 0;
	*last = ft_strlen(s1);
	while (is_set(s1[*begin], set) && s1[*begin])
		(*begin)++;
	while (is_set(s1[*last - 1], set) && *last >= *begin)
		(*last)--;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	b;
	size_t	l;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (ft_strlen(set) == 0)
		return (ft_strdup(s1));
	get_p(s1, set, &b, &l);
	if (l < b)
		return (ft_strdup(""));
	return (ft_substr(s1, (unsigned int)b, (unsigned int)(l - b)));
}
//int main(int argc, char **argv)
//{
//
//	char *p;
//	size_t	tst;
//
//	tst = sizeof(size_t);
//	printf("tst=%zu/n",tst);
//	p = ft_strtrim("hello world", "");
//	printf("p=%s\n",p);
//	if (argc == 3)
//	{
//		/*
//		char	*s1 = "  \t \t \n   \n\n\n\t";
//		char	*s3 = "   \t  \n\n \t\t  \n\n\nHello \t  Please\n Trim me !";
//		char	*s2 = " \n\t";
//		*/
//		p = ft_strtrim(argv[1],argv[2]);
//		//printf("input1=%s,input2=%s\n",argv[1],argv[2]);
//		printf("test1:output=%s:end\n",p);
//		
//		/*
//		p = ft_strtrim(s1,s2);
//		//printf("input1=%s,input2=%s\n",s1,s2);
//		printf("test2:output=%s:end\n",p);
//		p = ft_strtrim(s3,s2);
//		printf("test3:output=%s:end\n",p);
//		*/
//
//	}
//	return (0);
//}
