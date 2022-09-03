/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:20:54 by hsano             #+#    #+#             */
/*   Updated: 2022/07/18 00:44:29 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
//#include <stdlib.h>
//int main(int argc, char **argv)
//{
//	char c;
//	int	fd;
//	if (argc == 3)
//	{
//		c = argv[1][0];
//		fd = atoi(argv[2]);
//		ft_putchar_fd(c, fd);
//	}
//}
