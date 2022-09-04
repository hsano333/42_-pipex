/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 06:44:31 by hsano             #+#    #+#             */
/*   Updated: 2022/09/04 10:42:36 by hsano            ###   ########.fr       */
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
	heredoc = is_heredoc(argv);
	if (heredoc.valid)
		fd_in = 0;
	i = 1;
	while (++i < (argc - 1))
		fd_in = pipex(argv[i], fd_in, heredoc);
	fd_in = pipex("tee test_tee.txt", fd_in, heredoc);
	//free(cmds);
}
