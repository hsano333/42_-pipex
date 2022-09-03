/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:08:47 by hsano             #+#    #+#             */
/*   Updated: 2022/07/18 00:56:47 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;
	char	lf;

	if (!s)
		return ;
	lf = '\n';
	len = ft_strlen(s);
	write(fd, s, len);
	write(fd, &lf, 1);
}
//#include <stdlib.h>
//int main(int argc, char **argv)
//{
//	char *c;
//	int	fd;
//	if (argc == 3)
//	{
//		c = argv[1];
//		fd = atoi(argv[2]);
//		ft_putendl_fd(c, fd);
//	}
//}
