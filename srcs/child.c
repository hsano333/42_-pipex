/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:58:19 by hsano             #+#    #+#             */
/*   Updated: 2022/09/17 00:14:07 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_util.h"
#include "libft_str.h"

void	child(char *cmds, int fd_in, int pipe_fd[2])
{
	char		**argv;
	char		filepath[PATH_MAX + 1];
	extern char	**environ;
	int		result[4];

	argv = ft_split(cmds, ' ');
	if (argv)
	{
		if (search_path(argv[0], environ, filepath))
		{
			close(pipe_fd[PIPE_IN]);
			result[0] = close(0);
			result[1] = dup2(fd_in, 0);
			result[2] = close(1);
			result[3] = dup2(pipe_fd[PIPE_OUT], 1);
			if (result[0] == -1 || result[1] == -1 || result[2] == -1 || result[3] == -1)
				exit(EXIT_FAILURE);
			if (execve(filepath, argv, environ) == -1)
				exit(EXIT_FAILURE);
		}
	}
	ft_free_split(argv);
}

