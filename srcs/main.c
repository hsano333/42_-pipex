/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:31:44 by hsano             #+#    #+#             */
/*   Updated: 2022/09/13 12:45:57 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft_str.h"
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	int			fd_in;
	int			i;
	int			last_pid;
	char		tee_cmd[1024 + 10];
	t_heredoc	heredoc;

	if (argc != 5)
		kill_process(22, "Argument list size is only four\n");
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
		kill_process(0, NULL);
	heredoc.valid = false;
	i = 1;
	if (heredoc.valid)
		i++;
	while (++i < (argc - 1))
	{
		fd_in = pipex(argv[i], fd_in, heredoc, &last_pid);
		heredoc.valid = false;
	}
	ft_strlcpy(tee_cmd, "tee ", 5);
	ft_strlcat(tee_cmd, argv[argc - 1], 5 + ft_strlen(argv[argc - 1]));
	fd_in = pipex(tee_cmd, fd_in, heredoc, &last_pid);
	close(fd_in);
	return (0);
}
