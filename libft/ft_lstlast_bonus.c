/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:01:32 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 19:52:37 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//renvoie un pointeur sur le dernier node
#include "libft.h"
/*
t_list *ft_lstlast(t_list *lst);


int main (void)
{
        t_list  *node0;
        t_list  *node1;
        t_list  *node2;
        t_list  *node3;

        t_list  *test;

        node0 = ft_lstnew("Jean");
        node1 = ft_lstnew("Marc");
        node2 = ft_lstnew("Luc");
        node3 = ft_lstnew("Sam");
        ft_lstadd_front(&node1, node0);
        ft_lstadd_front(&node0, node2);
        ft_lstadd_front(&node0, node3);

	test = ft_malloc (sizeof(t_list));
	test = ft_lstlast(node3);
	printf ("%s",(char*)test->content);
}

*/

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
