/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:49:47 by wlouaked          #+#    #+#             */
/*   Updated: 2024/06/02 19:51:01 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_md(int nb, int clone, int fd);
static void	ft_translate(int number, int fd);
static void	ft_udcm(int nb, int clone, int fd );
void		ft_putnbr_fd(int n, int fd);
static void	ft_m(int nb, int clone, int fd);

/*
   int	main(void)
   {
   int	nbr;

   nbr = 0;
   ft_putnbr_fd(nbr, 2);
   return (0);
   }
*/

void	ft_putnbr_fd(int nb, int fd)
{
	int	clone;

	if (nb != -2147483648)
	{
		if (nb < 0)
		{
			nb = -nb;
			write(fd, "-", 1);
		}
		clone = nb;
		ft_md(nb, clone, fd);
		ft_m(nb, clone, fd);
		ft_udcm(nb, clone, fd);
		clone = nb % 10;
		ft_translate (clone, fd);
	}
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
}

static void	ft_translate(int number, int fd)
{
	char	letter;

	letter = 48 + number;
	write (fd, &letter, 1);
}

static void	ft_udcm(int nb, int clone, int fd)
{
	if (clone > 999)
	{
		clone = clone / 1000 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
	if (clone > 99)
	{
		clone = clone / 100 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
	if (clone > 9)
	{
		clone = clone / 10 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
}

static void	ft_m(int nb, int clone, int fd)
{
	if (clone > 999999)
	{
		clone = clone / 1000000 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
	if (clone > 99999)
	{
		clone = clone / 100000 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
	if (clone > 9999)
	{
		clone = clone / 10000 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
}

static void	ft_md(int nb, int clone, int fd)
{
	if (clone > 999999999)
	{
		clone = clone / 1000000000 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
	if (clone > 99999999)
	{
		clone = clone / 100000000 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
	if (clone > 9999999)
	{
		clone = clone / 10000000 % 10;
		ft_translate(clone, fd);
	}
	clone = nb;
}
