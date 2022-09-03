/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:11:07 by hsano             #+#    #+#             */
/*   Updated: 2022/09/04 01:45:19 by hsano            ###   ########.fr       */
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
	}
	errno = no;
	ft_printf("\n%s:%s\n", strerror(errno), message);
	exit(EXIT_FAILURE);
}

//int	get_fd(int argc, char **argv, int *fd_in, int *fd_out)
int	get_fd(int argc, char **argv, int *fd_in)
{
	*fd_in = open(argv[1], O_RDONLY);
	//*fd_out = open(argv[argc - 1], O_WRONLY);
	printf("get_fd test %s, %s\n",argv[1], argv[argc - 1]);
	if (*fd_in < 0)
	{
		perror(argv[2]);
		return (false);
	}
	/*
	if (*fd_out < 0)
	{
		//close(*fd_in);
		//perror(argv[argc - 1]);
		//return (false);
	}
	printf("get fd %d:%d\n", *fd_in, *fd_out);
	*/
	return (true);
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
