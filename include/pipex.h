/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:11:43 by hsano             #+#    #+#             */
/*   Updated: 2022/09/15 08:59:20 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define PIPE_IN 0
# define PIPE_OUT 1
# define READ_MAX 256
# define WRITE_MAX 256
# define HEREDOC_WORD "here_doc"
# include <unistd.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/wait.h>

typedef struct s_heredoc{
	int		valid;
	int		valid_backup;
	char	*limiter;
}	t_heredoc;

typedef struct s_fdpid{
	int		fd;
	int		pid;
}	t_fdpid;

void		kill_process(int no, char *message);
char		*search_path(char *exe, char **environ, char *filepath);
//int			pipex (char *cmds, int fd_in, t_heredoc heredoc);
//int	pipex(char *cmds, int fd_in, t_heredoc heredoc, int *last_pid);
//int	pipex(char *cmds, int fd_in, t_heredoc heredoc);
t_fdpid	pipex(char *cmds, int fd_in, t_heredoc heredoc);
t_heredoc	is_heredoc(char **argv);
t_fdpid	heredoc_input(t_heredoc heredoc);
int	check_valid_commands(int argc, char **argv, int *i);
#endif
