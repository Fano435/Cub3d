/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:11:05 by wlouaked          #+#    #+#             */
/*   Updated: 2024/05/28 16:45:18 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i])
	{
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
		{
			return (-1);
		}
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
		{
			return (1);
		}
		i++;
	}
	if (i < n && s1[i] == '\0' && s2[i] != '\0')
	{
		return (-1);
	}
	return (0);
}
