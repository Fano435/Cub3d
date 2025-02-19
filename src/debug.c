/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:37:50 by jrasamim          #+#    #+#             */
/*   Updated: 2025/02/19 16:46:47 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_square(int x, int y, int size, t_img *img)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	x *= BLOCK;
	y *= BLOCK;
	while (j++ < size)
	{
		pixel_put(img, x + j, y, 0xFFFFFF);
		pixel_put(img, x, y + j, 0xFFFFFF);
	}
	while (i++ < size)
	{
		pixel_put(img, x + i, y + j, 0xFFFFFF);
		pixel_put(img, x + j, y + i, 0xFFFFFF);
	}
}
/*REPLACED BY PRINT_MAP IN PARSING_MAP_UTILS*/
// void	draw_map(char map[10][8], t_img *img)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < 10)
// 	{
// 		x = 0;
// 		while (x < 8)
// 		{
// 			if (map[y][x] == '1')
// 				draw_square(x, y, BLOCK, img);
// 			x++;
// 		}
// 		y++;
// 	}
// }
