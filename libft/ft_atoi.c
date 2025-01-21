/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:34:27 by wlouaked          #+#    #+#             */
/*   Updated: 2024/05/28 17:54:49 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	val;
	int	is_neg;

	i = 0;
	is_neg = 1;
	val = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
			i++;
	if (str[i] == '-')
	{
		is_neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		val = val * 10 + (str[i] - '0');
		i++;
	}
	return (val * is_neg);
}
/*
 int	main(void)
{
	printf("%d\n", ft_atoi("-2147483648"));
	printf("%d\n", atoi("-2147483648"));
	printf("%d\n", ft_atoi("2147483647"));
	printf("%d\n", atoi("2147483647"));
	printf("%d\n", ft_atoi("0100000"));
	printf("%d\n", atoi("0100000"));
	printf("%d\n", ft_atoi("--2147483648"));
	printf("%d\n", atoi("--2147483648"));
	printf("%d\n", ft_atoi("+-2147483648"));
	printf("%d\n", atoi("+-2147483648"));
	printf("%d\n", ft_atoi("++2147483648"));
	printf("%d\n", atoi("++2147483648"));
}*/
