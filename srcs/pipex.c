/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 07:57:07 by hsano             #+#    #+#             */
/*   Updated: 2022/09/04 01:40:54 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft_str.h"
#include "ft_printf.h"

static void	child(char *cmds ,int fd_in, int fd[2])
{
	char		**argv;
	char		filepath[PATH_MAX + 1];
	extern char	**environ;

	printf("child process is start\n");
	argv = ft_split(cmds, ' ');
	int i = 0;
	if (argv)
	{
		printf("child process loop\n");
		if (search_path(argv[0], environ, filepath))
		{
			dup2(fd_in, 0);
			dup2(fd[PIPE_OUT], 1);
			printf("filepath:%s, argv[]:%s:%s", filepath, argv[0], argv[1]);
			execve(filepath , argv, environ);
			close(fd_in);
			close(fd[PIPE_IN]);
		}
		//free(argv[i]);
		i++;
	}
	printf("chile loop end\n");
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

static void	parent(void)
{
	ft_printf("parent process\n");
}

int	pipex (char *cmds, int fd_in, int fd_out)
{
	int			pid;
	int			status;
	int			pipefd[2];

	ft_printf("cmds=%s, fd_in=%d, fd_out=%d\n", cmds, fd_in, fd_out);
	if (pipe(pipefd) != 0)
		kill_process(0, "pipe() error\n");
	printf("success pipe()\n");
	pid = fork();
	if ((pid) == 0)
	{
		child(cmds, fd_in, pipefd);
		close(pipefd[PIPE_IN]);
		close(pipefd[PIPE_OUT]);
		exit(0);
	}
	else
	{
		ft_printf("parent process\n");
		if (waitpid(pid, &status, 0) < 0)
			kill_process(0, NULL);
		if (WIFEXITED(status) != 0)
			printf("child is exit\n");
		else if (WIFSIGNALED(status))
			printf("child is end by signal\n");

		//close(pipefd[PIPE_IN]);
		close(pipefd[PIPE_OUT]);
		parent();
	}
	//close(pipefd[PIPE_IN]);
	//close(pipefd[PIPE_OUT]);
	return (pipefd[PIPE_IN]);
}
