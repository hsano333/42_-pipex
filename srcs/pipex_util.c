/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:11:07 by hsano             #+#    #+#             */
/*   Updated: 2022/09/04 10:33:20 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"
#include "libft_str.h"

void	kill_process(int no, char *message)
{
	if (no == 0)
	{
		if (message)
			ft_printf("Error:%s\n", message);
		ft_printf("end pipex\n");
		exit(EXIT_FAILURE);
	}
	else if (no == -1)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	errno = no;
	if (message)
		ft_printf("\n%s:%s\n", strerror(errno), message);
	exit(EXIT_FAILURE);
}

static char	*concat_pathpath(char *filepath, char *env, char *exe)
{
	size_t	len;

	len = ft_strlen(env) + ft_strlen(exe) + 1 + 1;
	if (len > PATH_MAX + 1)
		kill_process(22, "Argument is too long\n");
	ft_strlcpy(filepath, env, ft_strlen(env) + 1);
	ft_strlcat(filepath, "/", ft_strlen(env) + 2);
	ft_strlcat(filepath, exe, len);
	return (filepath);
}

char	*search_path(char *exe, char **environ, char *filepath)
{
	size_t	i;
	size_t	j;
	char	**tmp_paths;
	char	*tmp;

	i = 0;
	while (environ[i])
	{
		tmp = ft_strchr(environ[i++], '=');
		if (!tmp)
			continue ;
		tmp_paths = ft_split(tmp, ':');
		j = 0;
		while (tmp_paths[j])
		{
			filepath = concat_pathpath(filepath, tmp_paths[j], exe);
			if (!access(filepath, X_OK))
				return (filepath);
			j++;
		}
	}
	return (NULL);
}

t_heredoc	is_heredoc(char **argv)
{
	t_heredoc	heredoc;

	if (ft_strncmp(argv[1], HEREDOC_WORD, ft_strlen(HEREDOC_WORD)) == 0)
	{
		printf("heredoc is valid\n");
		heredoc.valid = true;
		heredoc.limiter = argv[2];

	}
	else
	{
		printf("heredoc is invalid\n");
		heredoc.valid = false;
		heredoc.limiter= NULL;
	}
	return (heredoc);
}
