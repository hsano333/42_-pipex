/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 07:57:07 by hsano             #+#    #+#             */
/*   Updated: 2022/09/07 03:41:49 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"
#include "libft_str.h"
#include "ft_printf.h"
#include <sys/wait.h>
#define SHADOW_FILE "pipex_shadow_file.txt"

int	heredoc_input(t_heredoc heredoc)
{
	int	pid;
	int	pipe_fd[2];
	char	*line;
	int	fd;
	int	status;

	if (pipe(pipe_fd) != 0)
		kill_process(0, "pipe() error\n");
	//fd = 10;
	//if (fd < 0)
		//return ;
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[PIPE_IN]);
		//close(pipe_fd[PIPE_IN]);
		int i = 0;
		fd = open(SHADOW_FILE, (O_RDWR | O_CREAT), 0664);
		while(1)
		{
			//printf("input start i=%d\n",i);
			i++;
			//close(1);
			//dup2(pipe_fd[PIPE_OUT], 1);
			line = get_next_line(0);
			printf("heredoc input line=%s\n", line);
			//line = malloc(1000);

			//line[0] = 'a';
			//line[100] = 0;
			//printf("child line=%s\n", line);
			write(fd,line, ft_strlen(line));
			printf("heredoc input:line=%s\n",line);
			if (ft_strncmp(line, heredoc.limiter, ft_strlen(heredoc.limiter)) == 0)
			{
				printf("heredoc child is exit()\n");
				printf("heredoc child is exit()\n");
				printf("heredoc child is exit()\n");
				close(fd);
				close(0);
				exit(1);
			}
			else if (line)
				write(pipe_fd[PIPE_OUT], line, ft_strlen(line));
			free(line);
		}
	}
	else
	{
		close(pipe_fd[PIPE_OUT]);
		waitpid(pid, &status, 0);
	}
	printf("end heredoc!!!!!!!!!!!!!!!!!!!!!!!! \n");
	return (pipe_fd[PIPE_IN]);


}

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
		}
		i++;
	}
	ft_printf("chile loop end No.6 and free\n");
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


int	parent(int pid, int	*pipe_fd, t_heredoc heredoc, int *last_pid)
{
	int	pid_p;
	int	pipe_fd_p[2];
	int			status;
	char			buf[READ_MAX];
	size_t			read_size;
	size_t	sum;


	//close(pipe_fd[PIPE_IN]);
	if (pipe(pipe_fd_p) != 0)
		kill_process(0, "pipe() error\n");
	pid_p = fork();
	sum = 0;
	if ((pid_p) == 0)
	{
		ft_printf("tmp parent child No.0 \n");
		//close(pipe_fd_p[PIPE_OUT]);
		//while (waitpid(pid, &status, WNOHANG) == 0)
		while (1)
		{
			printf("tmp parent child No.0 \n");
			read_size = read(pipe_fd[PIPE_IN], buf, READ_MAX);
			printf("tmp parent child No.1 read_size=%zu,sum=%zu buf[0]=%c\n", read_size,sum, buf[0]);
			if (read_size > 0)
			{
				sum += read_size;
				write(pipe_fd_p[PIPE_OUT], buf, read_size);
				printf("tmp parent child write end No.1-1 read_size=%zu,sum=%zu buf[0]=%s\n", read_size,sum, buf);
			}
			if (read_size < READ_MAX)
			{
				printf("tmp parent child No.2 stop  read_size=%zu,sum=%zu buf[0]=%c\n", read_size,sum, buf[0]);
				waitpid(pid, &status, 0);
				break;
			}
		}
		ft_printf("tmp parent child No.3 end \n");
		close(pipe_fd[PIPE_IN]);
		close(pipe_fd_p[PIPE_OUT]);
		exit(1);
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
	if (sum > 0) { ft_printf("parent tempo write?: sum=%d:buf[0]:=%c%c\n",sum, buf[0],buf[1]);
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
	int		status;

	ft_printf("test No.3\n");
	if (fd_in == -1)
		return (-1);
	ft_printf("test No.4\n");
	if (pipe(pipe_fd) != 0)
		kill_process(0, "pipe() error\n");
	ft_printf("test No.5\n");
	pid = fork();
	ft_printf("test No.6\n");
	printf("No.0 first pid=%d\n", pid);
	if ((pid) == 0)
	{
		if (heredoc.valid)
		{
			heredoc.valid = false;
			printf("heredoc start\n");
			fd_in = heredoc_input(heredoc);
		}
		printf("next heredoc child\n");
		
		//int i = 0;
		//while(1)
		//{
			//i++;
		//}
		child(cmds, fd_in, pipe_fd, heredoc);
		exit(0);
	}
	else
	{
		while (1)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status) == true)
			{
				break;
				//break ;
			}
			else if (WIFSIGNALED(status) == true)
			{
				printf("signal exit is error?: status=%d\n", WEXITSTATUS(status));
				usleep(50000000);
				//ft_printf("brea No.2status=%d\n",status);
				//break ;
			}
			//if (WIFSTOPPED(status) == false)
			//{
				//ft_printf("proces is die\nerorr !!!!!!!!!!!!!!!!!!!!!!!\n");

			//}

		}

		printf("next heredoc parent\n");
		//child(cmds, fd_in, pipe_fd, heredoc);
		fd_in = parent(pid, pipe_fd, heredoc, last_pid);
	}
	return (fd_in);
}
