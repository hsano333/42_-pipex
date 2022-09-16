/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:06:12 by hsano             #+#    #+#             */
/*   Updated: 2022/09/17 00:41:45 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# define HEREDOC_WORD "here_doc"
t_fdpid		heredoc_input(t_heredoc *heredoc);
t_heredoc	is_heredoc(char **argv);
#endif
