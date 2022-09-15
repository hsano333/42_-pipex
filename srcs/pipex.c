/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 07:57:07 by hsano             #+#    #+#             */
/*   Updated: 2022/09/15 20:14:55 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft_str.h"
#include "ft_printf.h"

static void	child(char *cmds, int fd_in, int pipe_fd[2])
{
	char		**argv;
	char		filepath[PATH_MAX + 1];
	extern char	**environ;
	int		result[2];

	argv = ft_split(cmds, ' ');
	if (argv)
	{
		if (search_path(argv[0], environ, filepath))
		{
			close(pipe_fd[PIPE_IN]);
			close(0);
			result[0] = dup2(fd_in, 0);
			close(1);
			result[1] = dup2(pipe_fd[PIPE_OUT], 1);
			if (result[0] == -1 || result[1] == -1)
				exit(EXIT_FAILURE);
			execve(filepath, argv, environ);
		}
	}
	ft_free_split(argv);
	close(fd_in);
}

/*
static int	handling_error_in_parent(int *pipe_fd)
{
	close(pipe_fd[PIPE_IN]);
	return (-1);
}
*/

t_fdpid	parent(int pid, int	*pipe_fd)
{
	int		pid_p;
	int		pipe_fd_p[2];
	int		status;
	char	buf[READ_MAX];
	size_t	read_size;
	t_fdpid fdpid;

	if (pipe(pipe_fd_p) != 0)
		kill_process(0, "pipe() error\n");
	pid_p = fork();
	if ((pid_p) == 0)
	{
		while (1)
		{
			read_size = read(pipe_fd[PIPE_IN], buf, READ_MAX);
			if (read_size > 0)
			{
				write(pipe_fd_p[PIPE_OUT], buf, read_size);
			}
			if (read_size <= 0)
			{
				waitpid(pid, &status, 0);
				break ;
			}
		}
		close(pipe_fd[PIPE_IN]);
		close(pipe_fd_p[PIPE_OUT]);
		exit(0);
	}
	else
	{
		fdpid.pid = pid;
		fdpid.fd = pipe_fd_p[PIPE_IN];
		close(pipe_fd_p[PIPE_OUT]);
	}
	return (fdpid);
}

t_fdpid	pipex(char *cmds, int fd_in, t_heredoc heredoc)
{
	int		pid;
	int		pipe_fd[2];
	t_fdpid		fdpid;

	fdpid.pid = -1;
	if (pipe(pipe_fd) != 0)
		return (fdpid);
	pid = fork();
	if (pid == 0)
	{
		if (heredoc.valid == false)
			child(cmds, fd_in, pipe_fd);
		exit(0);
	}
	else if (pid > 0)
	{
		close(pipe_fd[PIPE_OUT]);
		if (heredoc.valid)
			fdpid = heredoc_input(heredoc);
		else 
			fdpid = parent(pid, pipe_fd);
	}
	return (fdpid);
}
