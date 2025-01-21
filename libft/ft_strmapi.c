/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:35:19 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 19:52:37 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
   char     ft_toupper2(unsigned int i, char c);

   char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

   int main (void)
   {
   char string[]="wayl";
   ft_strmapi(string, ft_toupper2);
   printf ("%s", string);
   }

   char     ft_toupper2(unsigned int i, char c)
   {

   if (c >= 'a' && c <= 'z')
   {
   c -= 32;
   }
   return (c);
   }
   */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*string;
	size_t		i;

	string = ft_malloc(sizeof(char) * ft_strlen(s) + 1);
	if (string == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		string[i] = f(i, (char )s[i]);
		i++;
	}
	string[i] = '\0';
	return (string);
}
