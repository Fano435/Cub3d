/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:57:37 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 20:26:35 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_split(char const *s, char c);
static int		ft_countword(char const *s, char c);
static int		len(char const *s, char c, int start);

char	**ft_split(char const *s, char c)
{
	char	**retval;
	int		i;
	int		start;

	retval = ft_malloc (sizeof(char *) * (ft_countword(s, c) + 1));
	if (!retval)
		return (NULL);
	i = 0;
	start = 0;
	while (s[start] == c)
		start++;
	while (i < ft_countword(s, c))
	{
		retval[i] = ft_substr(s, start, len(s, c, start));
		if (retval[i] == NULL)
			return (free_tab(retval));
		start += len(s, c, start);
		while (s[start] == c)
			start++;
		i++;
	}
	retval[ft_countword(s, c)] = NULL;
	return (retval);
}

static int	ft_countword(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static int	len(char const *s, char c, int start)
{
	int	len;

	len = 0;
	while (s[start] && s[start] != c)
	{
		len++;
		start++;
	}
	return (len);
}

char	**free_tab(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		ft_free(s[i]);
		i++;
	}
	ft_free(s);
	return (NULL);
}
