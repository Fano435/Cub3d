/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:28:54 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/05 22:59:48 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*clone;
	void	*content;

	head = NULL;
	while (lst)
	{
		content = f(lst->content);
		clone = ft_lstnew(content);
		if (clone == NULL)
			return (del(content), ft_lstclear(&head, del), NULL);
		ft_lstadd_back(&head, clone);
		lst = lst->next;
	}
	return (head);
}
