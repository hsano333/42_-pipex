/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:31:44 by hsano             #+#    #+#             */
/*   Updated: 2022/09/04 10:42:40 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int			fd_in;
	int			cnt;
	//char		**cmds;
	int			i;
	t_heredoc	heredoc;

	cnt = 1;
	if (argc != 5)
		kill_process(22, "Argument list size is only four\n");
	if ((fd_in = open(argv[1], O_RDONLY)) < 0)
		kill_process(0, NULL);
	heredoc.valid = false;
	i = 1;
	while (++i < (argc - 1))
		fd_in = pipex(argv[i], fd_in, heredoc);
	fd_in = pipex("tee test_tee.txt", fd_in, heredoc);
	//free(cmds);
}
