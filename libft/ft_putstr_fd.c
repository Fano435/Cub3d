/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:39:56 by wlouaked          #+#    #+#             */
/*   Updated: 2024/05/28 20:24:26 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = ft_strlen(s);
	while (i < nbr)
	{
		write (fd, &s[i], 1);
		i++;
	}
}
/*
int	main(void)
{
	char	*string = "Je suis un chat.";

	ft_putstr_fd(string, 1);
}
*/
