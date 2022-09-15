/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 06:44:31 by hsano             #+#    #+#             */
/*   Updated: 2022/09/15 07:52:38 by hsano            ###   ########.fr       */
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


void	write_file(int fd_in, char *filename, t_heredoc heredoc)
{
	int			fd_out; int			read_size;
	//int			k;
	char		buf[READ_MAX];
	int		option;
	mode_t		mode;
	//extern char	**environ;
	mode = 0777;


	/*
	k = 0;
	while (environ[k])
	{
		printf(" main environ[%d]=%s\n", k, environ[k]);
		k++;
	}
	*/
	if (heredoc.valid_backup)
	{
		printf("heredoc No.1\n");
		option = O_WRONLY | O_APPEND;
	}
	else
	{
		printf("heredoc No.2\n");
		option = O_WRONLY | O_CREAT | O_TRUNC;
	}
	printf("No.3 option=%d\n", option);
	fd_out = open(filename, option, mode);
	printf("No.1 fd_out=%d\n", fd_out);
	if (fd_out < 0)
	{
		if (heredoc.valid_backup)
		{
			option = O_WRONLY | O_CREAT;
			fd_out = open(filename, option, mode);
			printf(" remake No.2 fd_out=%d\n", fd_out);

		}
		if (fd_out < 0)
			kill_process(-1, filename);

	}
	printf("write file=%s , fd_out=%d\n",filename, fd_out);
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
	/*
	if (heredoc.valid)
	{
		fd_i++;
		fdpid[fd_i] = pipex(argv[i], fdpid[fd_i - 1].fd, heredoc);
		i++;
	}
	*/
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
	write_file(fdpid[fd_i].fd, argv[argc - 1], heredoc);
	printf("waitpid test No.1\n");
	printf("last end_i=%d, fd_i=%d\n", end_i, fd_i);
	while(end_i <= fd_i)
	{
		char *last="last waitpid\n\n";
		write(2, last, ft_strlen(last)); 
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
