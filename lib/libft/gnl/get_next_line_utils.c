/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:17:23 by hsano             #+#    #+#             */
/*   Updated: 2022/09/01 17:59:48 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *dest, char *src)
{
	size_t	i;

	i = 0;
	if (!src)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}

char	*ft_strnchr(const char *s, int c, size_t n)
{
	char	tmp;

	tmp = (char)c;
	while (*s && n--)
	{
		if (*s == tmp)
			return ((char *)s);
		s++;
	}
	if (tmp == '\0')
		return ((char *)s);
	return (NULL);
}
