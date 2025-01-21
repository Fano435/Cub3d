/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:59:31 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/02 19:45:59 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s1, char const *set);
static size_t	sizermstart(const char *s1, const char *s2);
static int		ft_search(char c, char *s);
static size_t	sizermend(const char *s1, const char *s2);

/*
   int	main (void)
   {
   char *string ="Je suis un chat de goutiere.";
   char *string2 = "Je .er";

   printf("%s", ft_strtrim(string, string2));
   }
   */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s3;
	int		sizes3;

	sizes3 = ft_strlen(s1) - (sizermstart(s1, set) + sizermend(s1, set));
	s3 = ft_substr (s1, (unsigned int)sizermstart(s1, set), sizes3);
	return ((char *)(s3));
}

static size_t	sizermstart(const char *s1, const char *s2)
{
	size_t	i;
	size_t	k;
	size_t	size;

	i = 0;
	k = 0;
	size = 0;
	while (s1[i])
	{
		k = ft_search(s1[i], (char *)s2);
		if (k == 1)
			size++;
		else
		{
			return (size);
		}
		i++;
	}
	return (size);
}

static size_t	sizermend(const char *s1, const char *s2)
{
	size_t	i;
	size_t	k;
	size_t	size;

	i = ft_strlen(s1) - 1;
	k = 0;
	size = 0;
	while (i > 0)
	{
		k = ft_search(s1[i], (char *)s2);
		if (k == 1)
			size++;
		else
		{
			return (size);
		}
		i--;
	}
	return (0);
}

static int	ft_search(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}
