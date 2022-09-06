/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:13:16 by hsano             #+#    #+#             */
/*   Updated: 2022/09/06 17:47:32 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while ((*(s++)))
		i++;
	return (i);
}
//#include <string.h>
//int main(int argc, char **argv)
//{
//
//	if (argc == 2)
//	{
//		printf("s=%s\n",argv[1]);
//		printf("my   len=%zu\n",ft_strlen((argv[1])));
//		printf("test len=%zu\n",strlen((argv[1])));
//		// setment error 
//		//printf("test null my=%zu\n",ft_strlen(NULL));
//		//printf("test null len=%zu\n",strlen(NULL));
//	}
//}
