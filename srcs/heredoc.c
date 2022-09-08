/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:18:48 by hsano             #+#    #+#             */
/*   Updated: 2022/09/08 08:02:29 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft_str.h"
#include "get_next_line.h"
#define SHADOW_FILE "pipex_shadow_file.txt"

static void	heredoc_child(int pipe_fd[2], t_heredoc heredoc)
{
	char	*line;
	int	fd;

	close(pipe_fd[PIPE_IN]);
	fd = open(SHADOW_FILE, (O_RDWR | O_CREAT), 0664);
	while(1)
	{
		line = get_next_line(0);
		write(fd,line, ft_strlen(line));
		if (ft_strncmp(line, heredoc.limiter, ft_strlen(heredoc.limiter)) == 0)
		{
			close(fd);
			close(0);
			break;
		}
		else if (line)
			write(pipe_fd[PIPE_OUT], line, ft_strlen(line));
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
		waitpid(pid, &status, 0);
	close(pipe_fd[PIPE_OUT]);
	return (pipe_fd[PIPE_IN]);
}
