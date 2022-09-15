/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 06:44:31 by hsano             #+#    #+#             */
/*   Updated: 2022/09/15 20:04:12 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft_str.h"
#include <sys/wait.h>

#include <unistd.h>

void	write_file(int fd_in, char *filename, t_heredoc heredoc)
{
	int			fd_out; int			read_size;
	char		buf[READ_MAX];
	int		option;
	mode_t		mode;
	mode = 0777;

	if (heredoc.valid_backup)
		option = O_WRONLY | O_APPEND;
	else
		option = O_WRONLY | O_CREAT | O_TRUNC;
	fd_out = open(filename, option, mode);
	if (fd_out < 0)
	{
		if (heredoc.valid_backup)
		{
			option = O_WRONLY | O_CREAT;
			fd_out = open(filename, option, mode);

		}
		if (fd_out < 0)
			kill_process(-1, filename);

	}
	while (1)
	{
		read_size = read(fd_in, buf, READ_MAX);
		if (read_size > 0)
			write(fd_out, buf, read_size);
		else
			break ;
	}
	close(fd_out);
}

int	check_arg(int argc, char **argv, t_fdpid* fdpid, t_heredoc *heredoc)
{
	int i;
	int fd_i;

	fd_i = 0;
	i = 2;
	printf("argc No.1\n");
	if (argc < 5)
		kill_process(22, "Argument list size is more than three\n");
	printf("argc No.2\n");
	*heredoc = is_heredoc(argv);
	printf("argc No.3\n");
	fdpid[fd_i].fd = open(argv[1], O_RDONLY);
	printf("argc No.4\n");
	if (heredoc->valid == false && fdpid[fd_i].fd < 0)
		kill_process(-1, argv[1]);
	printf("argc No.5\n");
	if (heredoc->valid)
		i++;
	printf("argc No.6\n");
	if (!check_valid_commands(argc, argv, &i))
		kill_process(22, argv[i]);
	printf("argc No.7\n");
	return (fd_i);
}

int 	main_child(int argc, char **argv)
{
	int			fd_i;
	int			i;
	t_fdpid			fdpid[4096];
	t_heredoc	heredoc;
	int			status;

	printf("main child No.1\n");
	fd_i = check_arg(argc, argv, fdpid, &heredoc);
	printf("main child No.2\n");
	i = 1;
	while (++i < (argc - 1))
	{
		fd_i++;
		printf("main child No.3\n");
		fdpid[fd_i] = pipex(argv[i], fdpid[fd_i - 1].fd, heredoc);
		printf("main child No.4\n");
		printf(" mainchild No.1 fdpid[fd_i]=%d\n", fdpid[fd_i].pid);
		if (fdpid[fd_i].pid == -1)
			kill_process(-1, "pipex error No.1");
		heredoc.valid = false;
	}
	write_file(fdpid[fd_i].fd, argv[argc - 1], heredoc);
	i = 0;
	while(++i <= fd_i)
	{
		waitpid(fdpid[i].pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0) 
			kill_process(-1, "pipex error No.2");
	}
	exit(0);
}

int	main(int argc, char **argv)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		main_child(argc, argv);
		exit(0);
	}
	else if (pid == -1)
		kill_process(-1, NULL);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0) 
		kill_process(0, NULL);

	return (0);
}
