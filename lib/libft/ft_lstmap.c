/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 00:40:22 by hsano             #+#    #+#             */
/*   Updated: 2022/07/18 23:02:37 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*allocate_memory_list(t_list *lst, void (*del)(void *))
{
	size_t	cnt;
	t_list	*p;
	t_list	*tmp;

	cnt = ft_lstsize(lst);
	p = NULL;
	while (cnt--)
	{
		tmp = (t_list *)malloc(sizeof(t_list));
		if (!tmp)
		{
			if (del)
				ft_lstclear(&p, del);
			return (NULL);
		}
		tmp->next = p;
		p = tmp;
	}
	return (p);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*bk;
	t_list	*p;

	if (!f || !lst)
		return (NULL);
	p = allocate_memory_list(lst, del);
	if (!p)
		return (NULL);
	bk = p;
	p->content = f(lst->content);
	while (lst->next)
	{
		lst = lst->next;
		p = p->next;
		p->content = f(lst->content);
	}
	return (bk);
}
