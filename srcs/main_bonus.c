/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 06:44:31 by hsano             #+#    #+#             */
/*   Updated: 2022/09/17 00:14:40 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_util.h"
#include "heredoc.h"
#include "libft_str.h"
#include <sys/wait.h>
#include <unistd.h>

static int	check_arg(int argc, char **argv, t_heredoc *heredoc)
{
	int	i;
	int	fd_in;

	i = 2;
	fd_in = 0;
	if (argc < 5)
		kill_process(22, "Argument list size is more than three\n");
	if (heredoc->valid == false)
	{
		fd_in = open(argv[1], O_RDONLY);
		if (fd_in < 0)
			kill_process(-1, argv[1]);
		close(fd_in);
	}
	if (heredoc->valid)
		i++;
	if (!check_valid_commands(argc, argv, &i))
		kill_process(22, argv[i]);
	return (true);
}


/*
int	pipex(int argc, char **argv)
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
*/

int	main(int argc, char **argv)
{
	t_heredoc	heredoc;
	char		*output_file;
	int		i;

	heredoc = is_heredoc(argv);
	if (check_arg(argc, argv, &heredoc))
	{
		i = 2;
		//if (heredoc.valid)
			//i = 3;
		output_file = argv[argc - 1];
		argv[argc - 1] = NULL;
		pipex(argv[1], output_file, &(argv[i]), &heredoc);
	}
	return (0);
}
