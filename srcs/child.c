/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:58:19 by hsano             #+#    #+#             */
/*   Updated: 2022/09/17 05:24:19 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_util.h"
#include "libft_str.h"

static void	put_invalid_command(char *cmds)
{
	write(2, "zsh: command not found: ", 25);
	write(2, cmds, ft_strlen(cmds));
	write(2, "\n", 1);
	exit(0);
}

void	child(char *cmds, int fd_in, int pipe_fd[2])
{
	char		**argv;
	char		filepath[PATH_MAX + 1];
	int			r[4];
	extern char	**environ;

	argv = ft_split(cmds, ' ');
	if (argv)
	{
		if (search_path(argv[0], environ, filepath))
		{
			close(pipe_fd[PIPE_IN]);
			r[0] = close(0);
			r[1] = dup2(fd_in, 0);
			r[2] = close(1);
			r[3] = dup2(pipe_fd[PIPE_OUT], 1);
			if (r[0] == -1 || r[1] == -1 || r[2] == -1 || r[3] == -1)
				exit(EXIT_FAILURE);
			if (execve(filepath, argv, environ) == -1)
				exit(EXIT_FAILURE);
		}
		else
			put_invalid_command(cmds);
	}
	ft_free_split(argv);
}
