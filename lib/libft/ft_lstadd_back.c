/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 00:36:40 by hsano             #+#    #+#             */
/*   Updated: 2022/08/08 20:28:56 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (new == NULL)
		return ;
	if (lst == NULL)
		lst = &new;
	if (lst[0] == NULL)
	{
		lst[0] = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}
