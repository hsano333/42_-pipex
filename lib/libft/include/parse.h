/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:26:08 by hsano             #+#    #+#             */
/*   Updated: 2022/08/12 00:04:54 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# define CONVERSIONS_CHAR "cspdiuxX% .#+-0123456789"
# define VALID_CONVERSIONS "cspdiuxX%"
# define INVALID_CONVERSIONS "oOfFeEgGlz"
# define FRONT 0
# define BACK 1
# include "common.h"
# include "libft_str.h"
int				ft_atoi_base(char *str, char *base, int *err);
int				ft_atoin(const char *str, size_t size, int mode);
void			info_conversion(t_conversion *convs);
void			check_error(const char *str, t_conversion *convs, \
							size_t middle_point, char *ascii_aray);
void			set_ascii(const char *str, size_t middle_point, \
												char *ascii_aray);
t_list			*parse_str(const char *str);
#endif
