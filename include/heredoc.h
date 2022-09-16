/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:06:12 by hsano             #+#    #+#             */
/*   Updated: 2022/09/17 00:11:58 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# define HEREDOC_WORD "here_doc"
t_heredoc	is_heredoc(char **argv);
t_fdpid	heredoc_input(t_heredoc *heredoc);
#endif
