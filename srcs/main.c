/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:31:44 by hsano             #+#    #+#             */
/*   Updated: 2022/09/04 01:46:19 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int			fd_in;
	//int			fd_out;
	int			cnt;
	char		**cmds;

	cnt = 1;
	if (argc != 5)
		kill_process(22, "Argument list size is only four\n");
	if (!get_fd(argc, argv, &fd_in))
		kill_process(0, NULL);
	cmds = (char **)malloc(sizeof(char *) * (argc - 2));
	if (!cmds)
		kill_process(12, "");
	cmds = &(argv[2]);
	cmds[argc - 3] = NULL;
	int i;
	i = 0;
	while (cmds[i])
	{
		printf("cmds:%s\n",cmds[i]);
		fd_in = pipex(cmds[i], fd_in, dup(0));
		i++;
	}
	fd_in = pipex("tee test_tee.txt", fd_in, dup(0));
	i = 0;
	printf("main No.2\n");
	//pipex(cmds, i++, fd_in, dup(0));
}
