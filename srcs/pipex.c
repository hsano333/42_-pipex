/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 07:57:07 by hsano             #+#    #+#             */
/*   Updated: 2022/09/04 10:41:55 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft_str.h"
#include "ft_printf.h"

static void	child(char *cmds , int fd_in, int pipe_fd[2], t_heredoc heredoc)
{
	char		**argv;
	char		filepath[PATH_MAX + 1];
	extern char	**environ;

	printf("child process is start heredoc valid:%d\n", heredoc.valid);
	argv = ft_split(cmds, ' ');
	int i = 0;
	if (argv)
	{
		printf("child process loop\n");
		if (search_path(argv[0], environ, filepath))
		{
			dup2(fd_in, 0);
			dup2(pipe_fd[PIPE_OUT], 1);
			printf("filepath:%s, argv[]:%s:%s", filepath, argv[0], argv[1]);
			execve(filepath , argv, environ);
			close(fd_in);
			close(pipe_fd[PIPE_IN]);
			close(pipe_fd[PIPE_OUT]);
		}
		//free(argv[i]);
		i++;
	}
	printf("chile loop end\n");
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

static int	handling_error_in_parent(int *pipe_fd)
{
	close(pipe_fd[PIPE_IN]);
	return (-1);
}

static int	parent(int pid, int	*pipe_fd, t_heredoc heredoc)
{
	int			status;

	/*
	if (t_heredoc.valid)
	{
		get_next_line(pipe_fd[PIPE_IN]);
	}
	*/
	ft_printf("parent process : heredoc valid:%d\n", heredoc.valid);
	close(pipe_fd[PIPE_OUT]);
	ft_printf("parent process\n");
	if (waitpid(pid, &status, 0) < 0)
		return (handling_error_in_parent(pipe_fd));
	else if (WIFEXITED(status))
		ft_printf("exit()\n");
		//return (handling_error_in_parent(pipe_fd));
	else if (!WIFSIGNALED(status))
		return (handling_error_in_parent(pipe_fd));
	return (pipe_fd[PIPE_IN]);
}

int	pipex(char *cmds, int fd_in, t_heredoc heredoc)
{
	int		pid;
	int		pipe_fd[2];
	int		next_fd;

	if (fd_in == -1)
		return (-1);
	if (pipe(pipe_fd) != 0)
		kill_process(0, "pipe() error\n");
	printf("success pipe()\n");
	pid = fork();
	if ((pid) == 0)
	{
		printf("cmds=%s,fd_in:%d/n",cmds,fd_in);
		child(cmds, fd_in, pipe_fd, heredoc);
		exit(0);
	}
	else
	{
		next_fd = parent(pid, pipe_fd, heredoc);
	}
	return (next_fd);
}
