/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_libft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:15:42 by aubertra          #+#    #+#             */
/*   Updated: 2025/03/07 10:09:10 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file needs to be deleted and these functions added to libft
but right now I am not able to use libft directly (compilation fails
and treats the functions form the libft as undefined)*/

#include "../include/cub3D.h"

/*Check is char is a space*/
int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

/*Check is char is a space*/
int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*compare two string for n characters*/
int	my_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*Compares two strings*/
int	my_strcmp(const char *s1, const char *s2)
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
