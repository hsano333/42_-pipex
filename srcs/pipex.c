/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 07:57:07 by hsano             #+#    #+#             */
/*   Updated: 2022/09/05 06:49:58 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft_str.h"
#include "ft_printf.h"
#include <sys/wait.h>

static void	child(char *cmds , int fd_in, int pipe_fd[2], t_heredoc heredoc)
{
	char		**argv;
	char		filepath[PATH_MAX + 1];
	extern char	**environ;

	ft_printf("child  No.1process is start heredoc valid:%d\n", heredoc.valid);
	argv = ft_split(cmds, ' ');
	int i = 0;
	if (argv)
	{
		ft_printf("child No.2 process loop start input fd=%d, pip_fd[0]:%d, pip_fd[1]:%d\n", fd_in, pipe_fd[0], pipe_fd[1]);
		if (search_path(argv[0], environ, filepath))
		{
			ft_printf("child No.3 process loop start input fd=%d, pip_fd[0]:%d, pip_fd[1]:%d\n", fd_in, pipe_fd[0], pipe_fd[1]);
			close(0);
			dup2(fd_in, 0);
			close(pipe_fd[PIPE_IN]);
			close(1);
			dup2(pipe_fd[PIPE_OUT], 1);
			execve(filepath , argv, environ);
			close(pipe_fd[PIPE_OUT]);
			close(fd_in);
		}
		i++;
	}
	ft_printf("chile loop end No.6 and free\n");
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

#define READ_MAX 4096

int	parent(int pid, int	*pipe_fd, t_heredoc heredoc, int *last_pid)
{
	int	pid_p;
	int	pipe_fd_p[2];
	int			status;
	char			buf[READ_MAX];
	size_t			read_size;
	//size_t	sum;


	//close(pipe_fd[PIPE_IN]);
	if (pipe(pipe_fd_p) != 0)
		kill_process(0, "pipe() error\n");
	pid_p = fork();
	//sum = 0;
	if ((pid_p) == 0)
	{
		ft_printf("tmp parent child No.0 \n");
		close(pipe_fd_p[PIPE_OUT]);
		while (waitpid(pid, &status, WNOHANG) == 0)
		{
			read_size = read(pipe_fd[PIPE_IN], buf, READ_MAX);
			ft_printf("tmp parent child No.1 read_size=%zu, buf[0]=%c\n", read_size, buf[0]);
			if (read_size > 0)
			{
				//sum = += read_size;
				write(pipe_fd_p[PIPE_OUT], buf, read_size);
			}
			if (read_size < READ_MAX)
			{
				ft_printf("tmp parent child No.2 stop  read_size=%zu, buf[0]=%c\n", read_size, buf[0]);
				waitpid(pid, &status, 0);
				break;
			}
		}
		close(pipe_fd[PIPE_IN]);
		close(pipe_fd_p[PIPE_OUT]);
	}
	else
	{
		close(pipe_fd[PIPE_OUT]);
		//close(pipe_fd[PIPE_IN]);
		close(pipe_fd_p[PIPE_OUT]);

	}
	ft_printf("parent process loop start pid=%d, pip_fd[0]:%d, pip_fd[1]:%d\n", pid, pipe_fd[0], pipe_fd[1]);
	ft_printf("parent start pid=%d, here_doc.valid=%d\n", pid, heredoc.valid);
	//*pid = pipe_fd_p[PIPE_IN];
	//pid = pid_p;
	*last_pid = pid_p;
	return pipe_fd_p[PIPE_IN];
	handling_error_in_parent(pipe_fd);
	/*
	if (t_heredoc.valid) { get_next_line(pipe_fd[PIPE_IN]);
	}
	*/
	/*
	ft_ft_printf("parent process : heredoc valid:%d\n", heredoc.valid);
	//close(pipe_fd[PIPE_OUT]);
	ft_ft_printf("parent process\n");
	int sum = 0;
	char	*buf;
	buf = malloc(75000);
	while (waitpid(pid, &status, WNOHANG) == 0)
	{
		ft_printf(" no.1 parent before read\n");
		read_size = read(pipe_fd[PIPE_IN], &(buf[sum]), READ_MAX);
		if (read_size > 0) { 
			sum += read_size;
			ft_printf("read_size=%zu,parent tempo write?: sum=%d:buf[0]:=%c%c\n",read_size,sum, buf[0],buf[1]);
			//write(pipe_fd[PIPE_OUT], buf, read_size);
			ft_printf("parent write end\n");
		}
		ft_printf("parent after read read_size=%ld,sum=%d:buf[0]:=%c%c%c%c\n", read_size,sum, buf[read_size-4],buf[read_size-3],buf[read_size-2], buf[read_size-1]);
		ft_printf("No.0 status=%d\n", status);
		if (read_size < READ_MAX)
		{
			if (WIFEXITED(status) != 0)
			{
				ft_printf("brea No.1status=%d\n", status);
				break ;
			}
			if (WIFSIGNALED(status) != 0)
			{
				ft_printf("brea No.2status=%d\n",status);
				break ;
			}
		}
			//return (handling_error_in_parent(pipe_fd));
	}
	//write(pipe_fd[PIPE_OUT], buf, read_size);
	//ft_printf("parent loop end read_size=%ld\n", read_size);
	ft_printf("No.3 wait parent\n");
	waitpid(pid, &status, 0);
	read_size = read(pipe_fd[PIPE_IN], &(buf[sum]), READ_MAX);
	ft_printf("No.2 parent loop end read read_size=%ld,sum=%d:buf[0]:=%c%c%c%c\n", read_size,sum, buf[read_size-4],buf[read_size-3],buf[read_size-2], buf[read_size-1]);
	ft_printf("No.4 end wait parent\n");
	if (WIFEXITED(status))
		ft_ft_printf("exit end \n");
		//return (handling_error_in_parent(pipe_fd));
	else if (WIFSIGNALED(status))
		return (handling_error_in_parent(pipe_fd));
	ft_printf("loop end No2\n");
	ft_printf("parent tempo write?: sum=%d:buf[0]:=%c%c\n",sum, buf[0],buf[1]);
	if (sum > 0) { 
		ft_printf("parent tempo write?: sum=%d:buf[0]:=%c%c\n",sum, buf[0],buf[1]);
		dup2(pipe_fd[PIPE_OUT], 1);
		write(pipe_fd[PIPE_OUT], buf, sum);
	}
	close(pipe_fd[PIPE_IN]);
	ft_ft_printf("parent process end return fd=%d\n", pipe_fd[PIPE_OUT]);
	*/
	return (pipe_fd[PIPE_OUT]);
}

int	pipex(char *cmds, int fd_in, t_heredoc heredoc, int *last_pid)
{
	int		pid;
	int		pipe_fd[2];
	//int		next_fd;

	if (fd_in == -1)
		return (-1);
	if (pipe(pipe_fd) != 0)
		kill_process(0, "pipe() error\n");
	ft_printf("success pipe()\n");
	pid = fork();
	if ((pid) == 0)
	{
		ft_printf("cmds=%s,fd_in:%d/n",cmds, fd_in);
		child(cmds, fd_in, pipe_fd, heredoc);
		exit(0);
	}
	else
	{
		close(pipe_fd[PIPE_OUT]);
		//close(pipe_fd[PIPE_IN]);
		fd_in = pipe_fd[PIPE_IN];
		*last_pid = pid;
		//printf("parent last:id=&d\n");

		//fd_in = parent(pid, pipe_fd, heredoc, last_pid);
		//next_fd = parent(pid, pipe_fd, heredoc);
	}
	
	//*last_pid = pid_p;
	return (fd_in);
}
