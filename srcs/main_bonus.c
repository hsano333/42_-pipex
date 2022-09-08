/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 06:44:31 by hsano             #+#    #+#             */
/*   Updated: 2022/09/08 08:14:18 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft_str.h"
#include <sys/wait.h>

void	write_file(int fd_in, char* filename)
{
	int	fd_out;
	char	buf[READ_MAX];
	int	read_size;

	fd_out = open(filename, O_WRONLY);
	while(1)
	{
		read_size = read(fd_in, buf, READ_MAX);
		if (read_size <= 0)
			break;
		if (read_size > 0)
			write(fd_out, buf, read_size);
	}
	close(fd_out);

}

int	main(int argc, char **argv)
{
	int			fd_in;
	int			i;
	t_heredoc	heredoc;
	int		last_pid;
	char		tee_cmd[1024+10];

	if (argc < 5)
		kill_process(22, "Argument list size is more than three\n");
	heredoc = is_heredoc(argv);
	if (heredoc.valid == false && (fd_in = open(argv[1], O_RDONLY)) < 0)
		kill_process(-1, NULL);
	i = 1;
	if (heredoc.valid)
		i++;
	while (++i < (argc - 1))
	{
		fd_in = pipex(argv[i], fd_in, heredoc, &last_pid);
		heredoc.valid = false;
	}
	ft_strlcpy(tee_cmd, "tee " , 5);
	ft_strlcat(tee_cmd, argv[argc - 1] , 5 + ft_strlen(argv[argc - 1]));
	fd_in = pipex(tee_cmd, fd_in, heredoc, &last_pid);
	close(fd_in);
	return (0);
}
