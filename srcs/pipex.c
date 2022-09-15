/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 07:57:07 by hsano             #+#    #+#             */
/*   Updated: 2022/09/15 19:38:19 by hsano            ###   ########.fr       */
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

	printf("pipex child No.1\n");
	argv = ft_split(cmds, ' ');
	if (argv)
	{
		if (search_path(argv[0], environ, filepath))
		{
			printf("pipex child No.2 filepath=%s, argv[0]=%s\n", filepath, argv[0]);
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
	printf("pipex child No.4\n");
	ft_free_split(argv);
	close(fd_in);
}

static int	handling_error_in_parent(int *pipe_fd)
{
	close(pipe_fd[PIPE_IN]);
	return (-1);
}

t_fdpid	parent(int pid, int	*pipe_fd)
{
	int		pid_p;
	int		pipe_fd_p[2];
	int		status;
	char	buf[READ_MAX];
	size_t	read_size;
	t_fdpid fdpid;

	printf("parent start No.1\n");
	if (pipe(pipe_fd_p) != 0)
	{
		printf("parent start error\n");
		kill_process(0, "pipe() error\n");
	}
	pid_p = fork();
	printf("parent start No.2 pid_p = %d\n", pid_p);
	if ((pid_p) == 0)
	{
		char *text1 = "parent start No.3\n";
		write(2, text1, ft_strlen(text1));
		printf("parent start No.3 pid_p = %d\n", pid_p);
		int i = 0;
		while (1)
		{
			//printf("parent start No.3\n");
			//char *text2 = "parent start read No.3\n";
			//write(2, text2, ft_strlen(text2));
			read_size = read(pipe_fd[PIPE_IN], buf, READ_MAX);
			//char *text3 = "parent start read end No.4\n";
			//write(2, text3, ft_strlen(text3));
			//printf("pid=%d, i=%d ,read_size=%zu,  i*read_size=%zu\n", pid, i ,read_size, i*read_size);
			i++;
			//buf[read_size - 1] = '\0';
			//printf("parent test buf=%s\n", buf);
			if (read_size > 0)
			{
				write(pipe_fd_p[PIPE_OUT], buf, read_size);
			}
			//if (read_size < READ_MAX)
			if (read_size <= 0)
			{
				char *text4 = "parent start read end  break No.5\n";
				write(2, text4, ft_strlen(text4));
				status = 1;
				printf("end parent child No.1, wait pid=%d status=%d\n",pid, status);
				waitpid(pid, &status, 0);
				printf("end parent child No.2, wait pid=%d status=%d\n",pid, status);
				break ;
			}
		}
		close(pipe_fd[PIPE_IN]);
		close(pipe_fd_p[PIPE_OUT]);
		printf("end parent child No.2\n");
		exit(0);
	}
	else
	{
		fdpid.pid = pid;
		fdpid.fd = pipe_fd_p[PIPE_IN];

		//close(pipe_fd[PIPE_OUT]);
		close(pipe_fd_p[PIPE_OUT]);
		//waitpid(pid_p, &status, 0);
	}

	return (fdpid);
	handling_error_in_parent(pipe_fd);
	//return (pipe_fd[PIPE_OUT]);
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
