/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:35:59 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 19:52:37 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;
	int		j;

	j = ft_strlen(src);
	i = 0;
	if (siz == 0)
		return (j);
	while (i < siz - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}
/*
int	main (void)
{
	char *string = "lorem ipsum dolor sit amet";
	char *string2;

	string2 = ft_malloc (sizeof(char) * ft_strlen(string));
	ft_strlcpy (string2, string, 0);
	printf("%s", string2);


}
*/
