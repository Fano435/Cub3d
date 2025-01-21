/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:36:18 by wlouaked          #+#    #+#             */
/*   Updated: 2024/05/24 20:42:30 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*string;
	char		*string2;
	size_t		i;

	if (!dest && !src)
		return (NULL);
	string = (char *)src;
	string2 = (char *)dest;
	i = 0;
	while (i < n)
	{
		string2[i] = string[i];
		i++;
	}
	return (dest);
}
