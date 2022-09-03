/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 00:53:22 by hsano             #+#    #+#             */
/*   Updated: 2022/08/14 03:21:32 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H
# define BASE_HEX_UPPER "0123456789ABCDEF"
# define BASE_HEX_LOWER "0123456789abcdef"
# define NULL_STR "(null)"
# define PRINT_SIZE_OVER (-1)
# define PUT_STR 0
# define GET_LEN 1

# include <unistd.h>
# include "common.h"
# include "libft_isto.h"
# include "libft_str.h"
# include "libft_put.h"
# include <inttypes.h>

char			*get_str_char(va_list *args, t_conversion *convs);
char			*get_str_str(va_list *args, t_conversion *convs);
char			*get_str_point(va_list *args, t_conversion *convs);
char			*get_str_int_digit(va_list *args, t_conversion *convs);
char			*get_str_uint_digit(va_list *args, t_conversion *convs);
char			*get_str_int_hex(va_list *args, t_conversion *convs);
char			*get_str_percent(va_list *args, t_conversion *convs);
char			*ft_strnbr_base(long long nbr, char *base);
char			*ft_strpointer_base(uintptr_t nbrl, char *base);
size_t			get_estimated_size(t_conversion *convs, char *str);
size_t			put_flag_minus(t_conversion *convs, char *str, char padding);
size_t			put_except_minus(t_conversion *convs, char *str, char padding);
size_t			ft_putstr_fd_wrapper(char *str, int fd, ssize_t *print_size);
int				print(const char *str, t_list *convs_list, va_list *args);
void			info_conversion(t_conversion *convs);
size_t			is_sign(t_conversion *convs, char *str);
void			fix_precision_and_minisize(char *str, t_conversion *convs);
#endif
