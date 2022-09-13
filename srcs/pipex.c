/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 07:57:07 by hsano             #+#    #+#             */
/*   Updated: 2022/09/13 12:39:02 by hsano            ###   ########.fr       */
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
	int			i;

	argv = ft_split(cmds, ' ');
	if (argv)
	{
		if (search_path(argv[0], environ, filepath))
		{
			printf("\nfilepath=%s\n", filepath);
			close(0);
			dup2(fd_in, 0);
			close(pipe_fd[PIPE_IN]);
			close(1);
			dup2(pipe_fd[PIPE_OUT], 1);
			execve(filepath, argv, environ);
			close(pipe_fd[PIPE_OUT]);
		}
	}
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
	close(fd_in);
}

static int	handling_error_in_parent(int *pipe_fd)
{
	close(pipe_fd[PIPE_IN]);
	return (-1);
}

int	parent(int pid, int	*pipe_fd, int *last_pid)
{
	int		pid_p;
	int		pipe_fd_p[2];
	int		status;
	char	buf[READ_MAX];
	size_t	read_size;

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
			if (read_size < READ_MAX)
			{
				waitpid(pid, &status, 0);
				break ;
			}
		}
		close(pipe_fd[PIPE_IN]);
		close(pipe_fd_p[PIPE_OUT]);
		exit(1);
	}
	else
	{
		close(pipe_fd[PIPE_OUT]);
		close(pipe_fd_p[PIPE_OUT]);
	}
	*last_pid = pid_p;
	return (pipe_fd_p[PIPE_IN]);
	handling_error_in_parent(pipe_fd);
	return (pipe_fd[PIPE_OUT]);
}

int	pipex(char *cmds, int fd_in, t_heredoc heredoc, int *last_pid)
{
	int		pid;
	int		pipe_fd[2];
	int		status;

	if (fd_in == -1)
		return (-1);
	if (pipe(pipe_fd) != 0)
		kill_process(0, "pipe() error\n");
	pid = fork();
	if ((pid) == 0)
	{
		if (heredoc.valid)
			fd_in = heredoc_input(heredoc);
		child(cmds, fd_in, pipe_fd);
		exit(0);
	}
	else
	{
		if (heredoc.valid)
		{
			while (1)
			{
				waitpid(pid, &status, 0);
				if (WIFEXITED(status) == true)
					break ;
			}
		}
		fd_in = parent(pid, pipe_fd, last_pid);
	}
	return (fd_in);
}
