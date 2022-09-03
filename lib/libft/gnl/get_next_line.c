/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:11 by hsano             #+#    #+#             */
/*   Updated: 2022/07/29 12:04:34 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	exist_lf(char **str, char **old_str, ssize_t i)
{
	char	*lf;

	lf = ft_strnchr(*str, '\n', i);
	if (lf)
	{
		if (lf[1] == '\0')
			*old_str = NULL;
		else
			*old_str = ft_strdup(lf + 1);
		lf[1] = '\0';
		return (true);
	}
	return (false);
}

int	check_eof(char **p, char **old_str, ssize_t read_num, ssize_t i)
{
	if (read_num < 0 && errno != EINTR)
	{
		free(*p);
		*p = NULL;
		*old_str = NULL;
		return (true);
	}
	else if (exist_lf(p, old_str, i))
		return (true);
	else if (read_num < BUFFER_SIZE)
	{
		if (i == 0)
		{
			free(*p);
			*p = NULL;
		}
		*old_str = NULL;
		return (true);
	}
	return (false);
}

char	*mange_memory(char *old_str, size_t m_size, size_t old_str_len)
{
	char	*p;

	p = malloc(m_size + old_str_len + 1);
	if (!p)
	{
		if (old_str)
			free(old_str);
		return (NULL);
	}
	p = ft_strcpy(p, old_str);
	if (old_str)
		free(old_str);
	return (p);
}

char	*read_fd(int fd, char **old_str, ssize_t m_size, ssize_t i)
{
	char	*str;
	ssize_t	old_str_len;
	ssize_t	read_num;

	old_str_len = i;
	str = mange_memory(*old_str, m_size, old_str_len);
	if (!str)
		return (NULL);
	read_num = BUFFER_SIZE;
	while (read_num == BUFFER_SIZE)
	{
		read_num = read(fd, &(str[i]), BUFFER_SIZE);
		if (read_num > 0)
			i += read_num;
		str[i] = '\0';
		if (check_eof(&str, old_str, read_num, i))
			return (str);
		if (i >= m_size + old_str_len - BUFFER_SIZE)
			return (read_fd(fd, &str, m_size, i));
	}
	return (str);
}

char	*get_next_line(int fd)
{
	size_t		m_size;
	size_t		old_str_size;
	char		*tmp;
	char		*swap;
	static char	*old_str[MAX_FD_SIZE] = {0};

	if (fd < 0 || fd >= MAX_FD_SIZE)
		return (NULL);
	if (BUFFER_SIZE <= 0)
		return (NULL);
	else if (BUFFER_SIZE > MIN_BUFFER_SIZE)
		m_size = BUFFER_SIZE;
	else
		m_size = MIN_BUFFER_SIZE;
	tmp = NULL;
	old_str_size = ft_strlen(old_str[fd]);
	if (old_str[fd] != NULL && (exist_lf(&(old_str[fd]), &tmp, old_str_size)))
	{
		swap = tmp;
		tmp = old_str[fd];
		old_str[fd] = swap;
		return (tmp);
	}
	return (read_fd(fd, &(old_str[fd]), m_size, old_str_size));
}
