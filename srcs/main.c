/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:31:44 by hsano             #+#    #+#             */
/*   Updated: 2022/09/07 13:27:55 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	int			fd_in;
	int			i;
	t_heredoc	heredoc;
	int		last_pid;
	int			status;
	char		*buf[4096];

	if (argc != 5)
		kill_process(22, "Argument list size is only four\n");
	if ((fd_in = open(argv[1], O_RDONLY)) < 0)
		kill_process(0, NULL);
	heredoc.valid = false;
	i = 1;
	while (++i < (argc - 1))
	{
		printf("start pipex i:%d, argv[i]=%s\n", i, argv[i]);
		fd_in = pipex(argv[i], fd_in, heredoc, &last_pid);
		heredoc.valid = false;
	}
	waitpid(last_pid, &status, 0);
	read(fd_in, buf, 1000);
	int fd_out = open(argv[argc -1], O_RDONLY);
	write(fd_out, buf, 1000);
	//fd_in = pipex("tee test_tee.txt", fd_in, heredoc, &last_pid);
	//waitpid(last_pid, &status, 0);
	close(fd_in);
	close(fd_out);
	//free(cmds);
	return (0);
}
