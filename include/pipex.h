/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:11:43 by hsano             #+#    #+#             */
/*   Updated: 2022/09/04 10:33:40 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define PIPE_IN 0
# define PIPE_OUT 1
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

typedef struct s_heredoc{
	int		valid;
	char	*limiter;
}	t_heredoc;

void		kill_process(int no, char *message);
char		*search_path(char *exe, char **environ, char *filepath);
int			pipex (char *cmds, int fd_in, t_heredoc heredoc);
t_heredoc	is_heredoc(char **argv);
#endif
