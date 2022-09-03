/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:29:36 by hsano             #+#    #+#             */
/*   Updated: 2022/07/16 18:47:46 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*memset_big_data(void *b, int c, size_t len, size_t i)
{
	size_t				loop;
	unsigned long long	tmp;
	unsigned char		tmp_c;
	size_t				tmp_len;
	unsigned long long	*p;

	p = (unsigned long long *)b;
	loop = sizeof(unsigned long long) / sizeof(unsigned char);
	tmp_len = len / loop;
	tmp_c = (unsigned char)c;
	tmp = tmp_c;
	i = loop - 1;
	while (i > 0)
		tmp = tmp | (unsigned long long)tmp_c << ((i--) * 8);
	i = 0;
	while (i++ < tmp_len)
		*(p++) = tmp;
	b = (unsigned char *)(p - tmp_len);
	tmp_len = tmp_len * loop;
	while (tmp_len < len)
		((unsigned char *)b)[tmp_len++] = tmp_c;
	return ((unsigned char *)b);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;

	i = 0;
	if (len > 128)
		return (memset_big_data(b, c, len, i));
	else
	{
		while (i < len)
			((unsigned char *)b)[i++] = c;
		return (b);
	}
}
