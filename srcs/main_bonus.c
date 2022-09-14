/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 06:44:31 by hsano             #+#    #+#             */
/*   Updated: 2022/09/14 21:00:12 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft_str.h"
#include <sys/wait.h>

#include <unistd.h>

int test(void) {
    char *file = "/bin/echo";
    char *const args[] = {"/bin/echo",  "echo Hello $ENV!", "$PATH", NULL};
    char *const env[] = {"ENV=World", NULL};

    printf("echo sanmple\n");
    execve(file, args, env);
    //execv(file, args);

    return 0;
}


void	write_file(int fd_in, char *filename)
{
	int			fd_out; int			read_size;
	//int			k;
	char		buf[READ_MAX];
	//extern char	**environ;


	/*
	k = 0;
	while (environ[k])
	{
		printf(" main environ[%d]=%s\n", k, environ[k]);
		k++;
	}
	*/
	fd_out = open(filename, O_WRONLY);
	printf("write file=%s , fd_out=%d\n",filename, fd_out);
	write(fd_out, "write_start\n", 12);

	while (1)
	{
		read_size = read(fd_in, buf, READ_MAX);
		if (read_size <= 0)
			break ;
		if (read_size > 0)
			write(fd_out, buf, read_size);
	}
	close(fd_out);
}

int	main(int argc, char **argv)
{
	int			fd_i;
	int			i;
	char		tee_cmd[1024 + 10];
	t_fdpid			fdpid[4096];
	t_heredoc	heredoc;


	fd_i = 0;
	//test();
	//return 0;
	if (argc < 5)
		kill_process(22, "Argument list size is more than three\n");
	heredoc = is_heredoc(argv);
	fdpid[fd_i].fd = open(argv[1], O_RDONLY);
	if (heredoc.valid == false && fdpid[fd_i].fd < 0)
		kill_process(-1, NULL);
	i = 1;
	if (heredoc.valid)
		i++;
	while (++i < (argc - 1))
	{
		fd_i++;
		printf("fd_i=%d, fdpid[fd_i-1]=%d\n", fd_i, fdpid[fd_i - 1].fd);
		fdpid[fd_i] = pipex(argv[i], fdpid[fd_i - 1].fd, heredoc);
		printf("return fdpid=%d\n", fdpid[fd_i].fd);
		heredoc.valid = false;
	}
	int end_i = 1;
	int status = 0;
	ft_strlcpy(tee_cmd, "tee ", 5);
	ft_strlcat(tee_cmd, argv[argc - 1], 5 + ft_strlen(argv[argc - 1]));

	//fd_i++;
	printf("tee end, fdpid[fd_i].fd=%d\n", fdpid[fd_i].fd);
	//fdpid[fd_i] = pipex(tee_cmd, fdpid[fd_i - 1].fd, heredoc);
	write_file(fdpid[fd_i].fd, "write_test.txt");
	printf("waitpid test No.1\n");
	char *last="last waitpid\n";
	write(2, last, ft_strlen(last)); 
	while(end_i <= fd_i)
	{
		status = 1;
		printf("last wait pid=%d,satus=%d\n", fdpid[end_i].pid, status);
		//write(2, last, ft_strlen(last)); 
		waitpid(fdpid[end_i].pid, &status, 0);
		//if (WIFEXITED(status) == true)
		//	break ;
		end_i++;

	}
	//close(fdpid);
	return (0);
}
