/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:36:24 by jrasamim          #+#    #+#             */
/*   Updated: 2025/01/16 17:36:25 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init(t_game *game)
{
	void	*win;

	game->img = malloc(sizeof(t_img));
	game->player = malloc(sizeof(t_player));
	init_player(game->player);
	game->mlx_ptr = mlx_init();
	win = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	game->win_ptr = win;
	game->img->mlx_img = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	game->img->addr = mlx_get_data_addr(game->img->mlx_img,
			&game->img->bits_per_pixel, &game->img->line_len,
			&game->img->endian);
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | (b));
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x >= WIN_WIDTH || x < 0 || y >= WIN_HEIGHT || y < 0)
		return ;
	offset = (y * img->line_len + x * (img->bits_per_pixel / 8));
	pixel = img->addr + offset;
	*(int *)pixel = color;
}

void	draw_square(int x, int y, int size, t_img *img)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
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

char	map[5][5] = {{'1', '1', '1', '1', '1'}, {'1', '0', '1', '0', '1'}, {'1',
		'0', '0', '0', '1'}, {'1', '0', '0', '0', '1'}, {'1', '1', '1', '1',
		'1'}};

void	draw_map(char map[5][5], t_img *img)
{
	int	x;
	int	y;
	int	size;

	size = 64;
	x = 0;
	while (x < 5)
	{
		y = 0;
		while (y < 5)
		{
			if (map[x][y] == '1')
				draw_square((x * size), (y * size), size, img);
			y++;
		}
		x++;
	}
}

void	draw_player(t_game *game)
{
	draw_square(game->player->x, game->player->y, 10, game->img);
}

int	render(t_game *game)
{
	move_player(game->player);
	draw_player(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img->mlx_img, 0,
		0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	(void)ac, (void)av;
	game = malloc(sizeof(t_game));
	init(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img->mlx_img, 0,
		0);
	mlx_hook(game->win_ptr, DestroyNotify, NoEventMask, close_game, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, key_press, game->player);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, key_release, game);
	// mlx_loop_hook(game->mlx_ptr, render, game);
	mlx_loop(game->mlx_ptr);
}
