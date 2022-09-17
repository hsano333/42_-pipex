/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:31:44 by hsano             #+#    #+#             */
/*   Updated: 2022/09/17 16:28:07 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_util.h"
#include "heredoc.h"
#include <sys/wait.h>
#include <unistd.h>

static int	check_arg(int argc, char **argv, t_heredoc *heredoc)
{
	int	i;
	int	fd_in;

	i = 2;
	fd_in = 0;
	if (argc != 5)
		kill_process(22, "Argument list size is only four\n", NULL);
	if (heredoc->valid == false)
	{
		fd_in = open(argv[1], O_RDONLY);
		if (fd_in < 0)
			kill_process(-1, argv[1], NULL);
		close(fd_in);
	}
	if (heredoc->valid)
		i++;
	return (true);
}

int	main(int argc, char **argv)
{
	int			i;
	char		*output_file;
	t_heredoc	heredoc;

	heredoc.valid = false;
	if (check_arg(argc, argv, &heredoc))
	{
		i = 2;
		output_file = argv[argc - 1];
		argv[argc - 1] = NULL;
		pipex(argv[1], output_file, &(argv[i]), &heredoc);
	}
	return (0);
}
