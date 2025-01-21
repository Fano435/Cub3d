/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:14:53 by wlouaked          #+#    #+#             */
/*   Updated: 2024/05/24 20:44:29 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	size_t		len;
	char		*returnstring;

	i = 0;
	len = ft_strlen(s);
	returnstring = NULL;
	while (i <= len)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			returnstring = ((char *)&s[i]);
		}
		if (!s[i] && !c)
			return ((char *)&s[i]);
		i++;
	}
	if (returnstring)
	{
		return (returnstring);
	}
	return (NULL);
}
