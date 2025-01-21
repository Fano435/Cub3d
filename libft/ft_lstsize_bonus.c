/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:09:53 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/04 18:58:58 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
int	ft_lstsize(t_list *lst);

int main (void)
{
	t_list	*node0;
	t_list	*node1;
	t_list	*node2;
        t_list  *node3;

	node0 = ft_lstnew("Jean");
	node1 = ft_lstnew("Marc");
        node2 = ft_lstnew("Luc");
        node3 = ft_lstnew("Sam");
	ft_lstadd_front(&node1, node0);
        ft_lstadd_front(&node0, node2);
        ft_lstadd_front(&node0, node3);

	printf("%d", ft_lstsize(node3));
}
*/
int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
