/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 06:44:31 by hsano             #+#    #+#             */
/*   Updated: 2022/09/15 08:59:02 by hsano            ###   ########.fr       */
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
	printf("check_arg No.1\n");
	if (argc < 5)
		kill_process(22, "Argument list size is more than three\n");
	printf("check_arg No.2\n");
	*heredoc = is_heredoc(argv);
	fdpid[fd_i].fd = open(argv[1], O_RDONLY);
	printf("check_arg No.3\n");
	if (heredoc->valid == false && fdpid[fd_i].fd < 0)
		kill_process(-1, argv[1]);
	printf("check_arg No.4\n");
	if (heredoc->valid)
		i++;
	printf("check_arg No.5\n");
	if (!check_valid_commands(argc, argv, &i))
		kill_process(22, argv[i]);
	printf("check_arg No.6\n");
	return (fd_i);
}

int	main(int argc, char **argv)
{
	int			fd_i;
	int			i;
	t_fdpid			fdpid[4096];
	t_heredoc	heredoc;

	fd_i = check_arg(argc, argv, fdpid, &heredoc);
	i = 1;
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
	write_file(fdpid[fd_i].fd, argv[argc - 1], heredoc);
	while(end_i <= fd_i)
	{
		waitpid(fdpid[end_i].pid, &status, 0);
		end_i++;
	}
	return (0);
}
