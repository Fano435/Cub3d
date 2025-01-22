/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:02:30 by wlouaked          #+#    #+#             */
/*   Updated: 2024/05/24 19:13:28 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*returnvalue;
	size_t			i;

	i = 0;
	returnvalue = (unsigned char *)s;
	while (i < n)
	{
		if ((unsigned char)returnvalue[i] == (unsigned char)c)
			return ((void *)&returnvalue[i]);
		i++;
	}
	return (NULL);
}
