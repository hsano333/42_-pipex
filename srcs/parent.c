/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:57:10 by hsano             #+#    #+#             */
/*   Updated: 2022/09/17 15:42:49 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_util.h"
#include "libft_str.h"
#include "ft_printf.h"

static void	parent_child(int pid, int *pipe_fd, int *pipe_fd_p)
{
	int		status;
	char	buf[READ_MAX];
	size_t	read_size;

	while (1)
	{
		read_size = read(pipe_fd[PIPE_IN], buf, READ_MAX);
		if (read_size > 0)
			write(pipe_fd_p[PIPE_OUT], buf, read_size);
		else if (read_size <= 0)
		{
			waitpid(pid, &status, 0);
			break ;
		}
	}
}

t_fdpid	parent(int pid, int *pipe_fd)
{
	int		pipe_fd_p[2];
	t_fdpid	fdpid;

	if (pipe(pipe_fd_p) != 0)
		kill_process(0, "parent():pipe() error\n", NULL);
	fdpid.pid = fork();
	if ((fdpid.pid) == 0)
	{
		close(pipe_fd_p[PIPE_IN]);
		parent_child(pid, pipe_fd, pipe_fd_p);
		close(pipe_fd[PIPE_IN]);
		close(pipe_fd_p[PIPE_OUT]);
		exit(0);
	}
	else if (fdpid.pid >= 0)
	{
		close(pipe_fd[PIPE_IN]);
		close(pipe_fd_p[PIPE_OUT]);
		fdpid.fd = pipe_fd_p[PIPE_IN];
	}
	return (fdpid);
}
