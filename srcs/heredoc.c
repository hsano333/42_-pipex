/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:18:48 by hsano             #+#    #+#             */
/*   Updated: 2022/09/17 15:46:41 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_util.h"
#include "heredoc.h"
#include "libft_str.h"
#include "get_next_line.h"

t_heredoc	is_heredoc(int argc, char **argv)
{
	t_heredoc	heredoc;

	heredoc.valid = false;
	heredoc.valid_backup = false;
	heredoc.limiter = NULL;
	if (argc < 5)
		return (heredoc);
	else if (ft_strncmp(argv[1], HEREDOC_WORD, ft_strlen(HEREDOC_WORD)) == 0)
	{
		heredoc.valid = true;
		heredoc.valid_backup = true;
		heredoc.limiter = argv[2];
	}
	return (heredoc);
}

static void	child_echo(int fd, char *echo_path, char *line, char **environ)
{
	int		pid;
	char	*argv[6];
	char	*line2;

	line2 = malloc(ft_strlen(line) + 10);
	if (!line2)
		kill_process(0, "heredoc malloc() error", NULL);
	ft_strlcpy(line2, "echo ", 10);
	ft_strlcat(line2, line, ft_strlen(line) + 10);
	argv[0] = "bash";
	argv[1] = "-c";
	argv[2] = line2;
	argv[3] = NULL;
	pid = fork();
	if (pid == 0)
	{
		close(1);
		dup2(fd, 1);
		execve(echo_path, argv, environ);
		exit(0);
	}
	else if (pid == -1)
		kill_process(0, "heredoc fork() error\n", NULL);
}

static void	heredoc_child(int pipe_fd[2], t_heredoc *heredoc)
{
	char		*line;
	char		echo_path[1024];
	int			r[2];
	char		*limiter;
	extern char	**environ;

	limiter = heredoc->limiter;
	r[0] = close(1);
	r[1] = dup2(pipe_fd[PIPE_OUT], 1);
	if (search_path("bash", environ, echo_path) == NULL \
			|| r[0] == -1 || r[0] == -1)
		kill_process(0, "heredoc_child() error", NULL);
	while (1)
	{
		errno = 0;
		write(2, "pipex heredoc> ", 15);
		line = get_next_line(0);
		if (errno > 0)
			kill_process(errno, "get_next_line() error", NULL);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break ;
		else if (line)
			child_echo(pipe_fd[PIPE_OUT], echo_path, line, environ);
		free(line);
	}
}

t_fdpid	heredoc_input(t_heredoc *heredoc)
{
	int		pid;
	int		pipe_fd[2];
	t_fdpid	fdpid;

	if (pipe(pipe_fd) != 0)
		kill_process(0, "heredoc pipe() error\n", NULL);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[PIPE_IN]);
		heredoc_child(pipe_fd, heredoc);
		close(pipe_fd[PIPE_OUT]);
		exit(0);
	}
	else
	{
		close(pipe_fd[PIPE_OUT]);
		fdpid.pid = pid;
		fdpid.fd = pipe_fd[PIPE_IN];
	}
	return (fdpid);
}
