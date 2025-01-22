/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:48:53 by wlouaked          #+#    #+#             */
/*   Updated: 2024/05/24 19:57:36 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*ptsrc;
	char		*ptdst;
	size_t		i;

	ptsrc = (char *)src;
	ptdst = (char *)dest;
	if (ptdst > ptsrc)
	{
		i = n;
		while (i > 0)
		{
			i--;
			ptdst[i] = ptsrc[i];
		}
	}
	else if (ptdst < ptsrc)
	{
		i = 0;
		while (i < n)
		{
			ptdst[i] = ptsrc[i];
			i++;
		}
	}
	return (dest);
}
