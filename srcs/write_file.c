/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:28:23 by hsano             #+#    #+#             */
/*   Updated: 2022/09/17 03:02:35 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_util.h"

static void	write_file_heredoc(int fd_in, char *filename)
{
	int		fd_out;
	int		read_size;
	int		option;
	char	buf[READ_MAX];

	option = O_WRONLY | O_APPEND;
	fd_out = open(filename, option, 0777);
	if (fd_out < 0)
	{
		option = O_WRONLY | O_CREAT;
		fd_out = open(filename, option, 0777);
		if (fd_out < 0)
			kill_process(-1, filename, NULL);
	}
	while (1)
	{
		read_size = read(fd_in, buf, READ_MAX);
		if (read_size > 0)
			write(fd_out, buf, read_size);
		else
			break ;
	}
}

void	write_file(int fd_in, char *filename, t_heredoc *heredoc)
{
	int		fd_out;
	int		read_size;
	int		option;
	char	buf[READ_MAX];

	if (heredoc->valid_backup)
	{
		write_file_heredoc(fd_in, filename);
		return ;
	}
	option = O_WRONLY | O_CREAT | O_TRUNC;
	fd_out = open(filename, option, 0777);
	if (fd_out < 0)
		kill_process(-1, filename, NULL);
	while (1)
	{
		read_size = read(fd_in, buf, READ_MAX);
		if (read_size > 0)
			write(fd_out, buf, read_size);
		else
			break ;
	}
	close(fd_out);
}
