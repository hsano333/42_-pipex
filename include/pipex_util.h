/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:09:22 by hsano             #+#    #+#             */
/*   Updated: 2022/09/17 03:02:53 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_UTIL_H
# define PIPEX_UTIL_H
# define PIPE_IN 0
# define PIPE_OUT 1
# define READ_MAX 256
# define WRITE_MAX 256
int		check_valid_commands(int argc, char **argv, int *i);
void	kill_process(int no, char *message1, char *message2);
char	*search_path(char *exe, char **environ, char *filepath);
#endif
