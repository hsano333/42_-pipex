/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 01:41:48 by hsano             #+#    #+#             */
/*   Updated: 2022/08/11 14:31:49 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H
# define BASE_DIGIT "0123456789"
# define NONE -1
# define ZERO 0
# define OVERFLOW -4
# define MEMORY_ERROR -5
# define ERROR_ATOI -3

# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include "libft_lst.h"

typedef struct s_conversion
{
	size_t		size;
	const char	*point;
	char		conversion;
	int			mini_width;
	int			precision;
	int			flag_minus;
	int			flag_plus;
	int			flag_sharp;
	int			flag_space;
	int			flag_zero;
	int			valid;
	int			mem_err;
	int			minus_value;
	int			free_str;
	char		sharp_str[2];
	size_t		arg_len;
	size_t		print_size;
}				t_conversion;

void			clear_conversion(t_conversion *node);
#endif
