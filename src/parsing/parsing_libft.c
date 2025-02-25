/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_libft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:15:42 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/25 15:11:12 by aubertra         ###   ########.fr       */
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

/*copy a string*/
char	*my_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*Get len of a string*/
int	my_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

/*Copy a string in a new, malloced string*/
char	*my_strdup(char *s)
{
	char	*string;

	string = (char *)malloc(sizeof(char) * my_strlen(s) + 1);
	if (!string)
		return (NULL);
	my_strcpy(string, s);
	return (string);
}
