/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:33:43 by wlouaked          #+#    #+#             */
/*   Updated: 2024/05/30 17:37:32 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void    ft_toupper2(unsigned int i, char *c);

int     main (void)
{
        char string[] = "wayl et maya";

        ft_striteri(string,ft_toupper2);
        printf("%s", string);
}

void    ft_toupper2(unsigned int i, char *c)
{
        if (*c >= 'a' && *c <= 'z')
        {
                *c -= 32;
        }
        return ;
}
*/
