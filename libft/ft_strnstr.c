/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:37:27 by wlouaked          #+#    #+#             */
/*   Updated: 2024/05/28 16:39:32 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*big2;
	size_t	i;
	size_t	len_little;

	i = 0;
	big2 = (char *) big;
	if (little[0] == '\0')
		return (big2);
	len_little = ft_strlen(little);
	while (big2[i] && i + len_little - 1 < len)
	{
		if (big2[i] == little[0])
		{
			if (!ft_strncmp(&big2[i], little, len_little))
				return (&big2[i]);
		}
		i++;
	}
	return (NULL);
}
// int main(void)
// {
//         char haystack[30] = "coucou, comment tu vas ?";
//         char needle[10] = "co";
//         char * empty = (char*)"";
//         /* 1 */ printf("%s\n", ft_strnstr(haystack, needle, 0));
//         /* 2 */ printf("%s\n", ft_strnstr(haystack, needle, -1));
//         /* 3 */ printf("%s\n", ft_strnstr(haystack, "a", -1));
//         /* 4 */ printf("%s\n", ft_strnstr(haystack, "c", -1));
//         /* 5 */ printf("%s\n", ft_strnstr(empty, "", -1));
//         /* 6 */ printf("%s\n", ft_strnstr(empty, "", 0));
//         /* 7 */ printf("%s\n", ft_strnstr(empty, "coucou", -1));
//         /* 8 */ printf("%s\n", ft_strnstr(haystack, "aaabc", 5));
//         /* 9 */ printf("%s\n", ft_strnstr(empty, "12345", 5));
//         /* 10 */ printf("%s\n", ft_strnstr(haystack, "abcd", 9));
//         /* 11 */ printf("%s\n", ft_strnstr(haystack, "cd", 8));
//         /* 12 mbueno-g */ printf("%s\n", ft_strnstr(haystack, "a", 1));
//         /* 13 opsec-infosec */ printf("%s\n", ft_strnstr("1", "a", 1));
//         /* 14 opsec-infosec */ printf("%s\n", ft_strnstr("22", "b", 2));
//         return (0);
// }
//on cherche la premiere lettre egale
//si la premiere lettre est egale, on fait un strncmp len(little)
//si strncmp renvoie ok on retourne le pointeur qui parcourt big
//sinon on continue
//si on a parcouru les *len* premiers caracteres de big, on retourne null
