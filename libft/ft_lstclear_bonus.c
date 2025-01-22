/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:07:42 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/05 16:08:17 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*clone;

	if (lst && *lst)
	{
		while (*lst)
		{
			clone = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = clone;
		}
		*lst = NULL;
	}
}
