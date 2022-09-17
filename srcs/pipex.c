/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 07:57:07 by hsano             #+#    #+#             */
/*   Updated: 2022/09/17 15:43:03 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "parent.h"
#include "child.h"
#include "write_file.h"
#include "libft_str.h"
#include "ft_printf.h"
#include "heredoc.h"
#include "pipex_util.h"

t_fdpid	pipe_main(char *cmds, int fd_in, t_heredoc *heredoc)
{
	int		pipe_fd[2];
	t_fdpid	fdpid;

	fdpid.pid = -1;
	if (pipe(pipe_fd) != 0)
		return (fdpid);
	fdpid.pid = fork();
	if (fdpid.pid == 0)
	{
		close(pipe_fd[PIPE_IN]);
		if (heredoc->valid == false)
			child(cmds, fd_in, pipe_fd);
		exit(0);
	}
	else if (fdpid.pid > 0)
	{
		close(pipe_fd[PIPE_OUT]);
		if (heredoc->valid)
			fdpid = heredoc_input(heredoc);
		else
			fdpid = parent(fdpid.pid, pipe_fd);
	}
	if (fd_in > 0)
		close(fd_in);
	return (fdpid);
}

static void	main_child(char **cmds, \
		char *output_file, t_fdpid *fdpid, t_heredoc *heredoc)
{
	int		i;
	int		fd_i;
	int		status;

	i = 0;
	fd_i = 0;
	if (heredoc->valid)
		fd_i++;
	while (cmds[i])
	{
		fd_i++;
		fdpid[fd_i] = pipe_main(cmds[i++], fdpid[fd_i - 1].fd, heredoc);
		if (fdpid[fd_i].pid == -1)
			kill_process(-1, "pipex error:fork() error", NULL);
		heredoc->valid = false;
	}
	write_file(fdpid[fd_i].fd, output_file, heredoc);
	i = fd_i;
	while (i > 0)
	{
		waitpid(fdpid[i].pid, &status, 0);
		i--;
	}
}

int	pipex(char *input_file, char *output_file, char **cmds, t_heredoc *heredoc)
{
	int		pid;
	int		status;
	t_fdpid	fdpid[4096];

	fdpid[0].fd = 0;
	if (heredoc->valid == false)
		fdpid[0].fd = open(input_file, O_RDONLY);
	if (fdpid[0].fd == -1)
		kill_process(-1, input_file, NULL);
	pid = fork();
	if (pid == 0)
	{
		main_child(cmds, output_file, fdpid, heredoc);
		exit(0);
	}
	else if (pid == -1)
		kill_process(-1, NULL, NULL);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		kill_process(0, NULL, NULL);
	return (0);
}
