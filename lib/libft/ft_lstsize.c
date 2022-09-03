/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 00:34:33 by hsano             #+#    #+#             */
/*   Updated: 2022/08/09 02:20:23 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	cnt;

	cnt = 0;
	if (!lst)
		return ((int)cnt);
	cnt++;
	while (lst->next)
	{
		cnt++;
		lst = lst->next;
	}
	if (cnt > INT_MAX)
		return (-1);
	return ((int)cnt);
}
