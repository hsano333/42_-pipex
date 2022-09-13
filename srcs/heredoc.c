/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:18:48 by hsano             #+#    #+#             */
/*   Updated: 2022/09/13 07:59:20 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft_str.h"
#include "get_next_line.h"
#define SHADOW_FILE "pipex_shadow_file.txt"

static void	child_echo(int fd, char *echo_path, char **argv, char **environ)
{
	int pid;


	/*
       int k = 0;
       while (environ[k])
       {
               printf(" main environ[%d]=%s\n", k, environ[k]);
               k++;
       }

       */

	printf("path=%s, fd=%d, argv[0]=%s, [1]=%s, [2]=%s,\n",echo_path, fd, argv[0], argv[1], argv[2]);
	pid = fork();
	if (pid == 0)
	{
		//close(1);
		//dup2(fd, 1);
		execve(echo_path, argv, environ);
		exit(0);
	}
}

static void	heredoc_child(int pipe_fd[2], t_heredoc heredoc)
{
	int			fd;
	char		*line;
	char		*argv[4];
	char		echo_path[128];
	extern char	**environ;

	if (search_path("echo", environ, echo_path) == NULL)
		kill_process(0, "Error:don't find echo\n");
	argv[0] = "echo";
	argv[1] = "-n";
	argv[3] = NULL;
	close(pipe_fd[PIPE_IN]);
	fd = open(SHADOW_FILE, (O_RDWR | O_CREAT), 0664);
	close(1);
	dup2(pipe_fd[PIPE_OUT], 1);
	while (1)
	{
		line = get_next_line(0);
		argv[2] = line;
		if (ft_strncmp(line, heredoc.limiter, ft_strlen(heredoc.limiter)) == 0)
		{
			close(fd);
			close(0);
			break ;
		}
		else if (line)
			child_echo(pipe_fd[PIPE_OUT], echo_path, argv, environ);
		free(line);
	}
}

int	heredoc_input(t_heredoc heredoc)
{
	int	pid;
	int	pipe_fd[2];
	int	status;

	if (pipe(pipe_fd) != 0)
		kill_process(0, "pipe() error\n");
	pid = fork();
	if (pid == 0)
	{
		heredoc_child(pipe_fd, heredoc);
		exit(0);
	}
	else
	{
		while (1)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status) == true)
				break ;
		}
	}
	printf("heredoc end parend\n");
	close(pipe_fd[PIPE_OUT]);
	return (pipe_fd[PIPE_IN]);
}
