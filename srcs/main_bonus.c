/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 06:44:31 by hsano             #+#    #+#             */
/*   Updated: 2022/09/05 08:47:10 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

void	write_file(int fd_in, char* filename)
{
	int	fd_out;
	char	buf[READ_MAX];
	int	read_size;

	fd_out = open(filename, O_WRONLY);
	while(1)
	{
		read_size = read(fd_in, buf, READ_MAX);
		printf("last write read_size=%d\n", read_size);
		if (read_size <= 0)
			break;
		if (read_size > 0)
			write(fd_out, buf, read_size);
	}
	printf("last write end\n");
	close(fd_out);

}

int	main(int argc, char **argv)
{
	int			fd_in;
	//char		**cmds;
	int			i;
	t_heredoc	heredoc;
	int		last_pid;
	//int			*pid_array;
	int			status;
	//char		buf[4096];

	if (argc < 5)
		kill_process(22, "Argument list size is more than three\n");
	if ((fd_in = open(argv[1], O_RDONLY)) < 0)
		kill_process(-1, NULL);
	//cmds = (char **)malloc(sizeof(char *) * (argc - 2));
	//if (!cmds)
		//kill_process(-1, NULL);
	//cmds = &(argv[2]);
	//cmds[argc - 3] = NULL;
	//i = 0;
	//pid_array = (int *)malloc(sizeof(int *) * argc);
	heredoc = is_heredoc(argv);
	if (heredoc.valid)
		fd_in = 0;
	i = 1;
	while (++i < (argc - 1))
	{
		fd_in = pipex(argv[i], fd_in, heredoc, &last_pid);
	}
	fd_in = pipex("tee test_tee.txt", fd_in, heredoc, &last_pid);
	write_file(fd_in, argv[argc - 1]);
	//waitpid(last_pid, &status, 0);
	/*
	read(fd_in, buf, 1000);
	int fd_out = open(argv[argc -1], O_WRONLY);
	printf("write_file:%s, fd_out=%d, buf[0]=%c,%c\n",argv[argc-1], fd_out, buf[0],buf[1]);
	buf[999] = 'a';
	buf[9] = 'a';
	write(fd_out, &(buf[0]), 1000);
	write(1, &(buf[0]), 1000);
	//fd_in = pipex("tee test_tee.txt", fd_in, heredoc, &last_pid);
	//waitpid(last_pid, &status, 0);
	close(fd_out);
	*/
	status = 1;
	close(fd_in);
	//free(cmds);
	return (status);
}
