/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:11:07 by hsano             #+#    #+#             */
/*   Updated: 2022/09/17 05:45:57 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"
#include "libft_str.h"

void	kill_process(int no, char *message1, char *message2)
{
	dup2(2, 1);
	if (no == 0)
	{
		if (message1 || message2)
			ft_printf("Error:%s:%s\n", message1, message2);
		else if (message1)
			ft_printf("Error:%s\n", message1);
		ft_printf("end pipex\n");
		exit(EXIT_FAILURE);
	}
	else if (no == -1)
	{
		perror(message1);
		exit(EXIT_FAILURE);
	}
	errno = no;
	if (message1)
		ft_printf("\n%s:%s\n", strerror(errno), message1);
	exit(EXIT_FAILURE);
}

static char	*concat_pathpath(char *filepath, char *env, char *exe)
{
	size_t	len;

	len = ft_strlen(env) + ft_strlen(exe) + 1 + 1;
	if (len > PATH_MAX + 1)
		kill_process(22, "Argument is too long\n", NULL);
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
			filepath = concat_pathpath(filepath, tmp_paths[j++], exe);
			if (!access(filepath, X_OK))
			{
				ft_free_split(tmp_paths);
				return (filepath);
			}
		}
		ft_free_split(tmp_paths);
	}
	return (NULL);
}

int	check_valid_commands(int argc, char **argv, int *i)
{
	extern char	**environ;
	char		**split;
	char		filepath[PATH_MAX + 1];
	int			error;

	while (*i < argc - 1)
	{
		error = false;
		split = ft_split(argv[*i], ' ');
		if (split)
		{
			if (search_path(split[0], environ, filepath) == NULL)
				error = true;
		}
		else
			error = true;
		ft_free_split(split);
		if (error)
			return (false);
		(*i)++;
	}
	return (true);
}
