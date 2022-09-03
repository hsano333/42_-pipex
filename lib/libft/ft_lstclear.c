/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 00:38:37 by hsano             #+#    #+#             */
/*   Updated: 2022/07/17 03:06:38 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*next;

	if (!del || !lst || !(*lst))
		return ;
	tmp = *lst;
	while (tmp->next)
	{
		next = tmp->next;
		ft_lstdelone(tmp, del);
		free(tmp);
		tmp = next;
	}
	ft_lstdelone(tmp, del);
	free(tmp);
	*lst = NULL;
}
