/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:46:19 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 19:52:37 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb == 0)
	{
		p = ft_malloc(0);
		return (p);
	}
	if (size == 0)
	{
		p = ft_malloc(0);
		return (p);
	}
	if (((size_t) - 1 / nmemb) < size)
		return (NULL);
	p = ft_malloc (nmemb * size);
	if (!p)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return (p);
}
/*
int	main()
{
	char *string;

	string = ft_calloc(0,sizeof(char));
	if(!string)
		printf("SUCCESS");

}*/
