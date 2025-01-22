/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:16:43 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 20:28:23 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			count;
	unsigned char	*s1_2;
	unsigned char	*s2_2;

	s1_2 = (unsigned char *)s1;
	s2_2 = (unsigned char *)s2;
	count = 0;
	while (s2_2[count] || s1_2[count])
	{
		if (s1_2[count] != s2_2[count])
		{
			if (s1_2[count] < s2_2[count])
				return (-1);
			return (EXIT_FAILURE);
		}
		count++;
	}
	return (EXIT_SUCCESS);
}
