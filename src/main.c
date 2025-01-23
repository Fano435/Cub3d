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

char	map[10][8] = {{'1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '0', '1',
		'0', '0', '0', '0', '1'}, {'1', '0', '1', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '0', '1'}, {'1', '0', '0', '0', '0', '1',
		'0', '1'}, {'1', '0', '1', '0', '0', '0', '0', '1'}, {'1', '0', '0',
		'0', '0', '0', '0', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1'}};

void	draw_map(char map[10][8], t_img *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < 10)
	{
		y = 0;
		while (y < 8)
		{
			if (map[x][y] == '1')
				draw_square((x * BLOCK), (y * BLOCK), BLOCK, img);
			y++;
		}
		x++;
	}
}

void	clear(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			pixel_put(game->img, i, j, 0x000000);
			j++;
		}
		i++;
	}
}

bool	touch(float px, float py, char map[10][8])
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (px >= WIN_WIDTH || px <= 0 || py >= WIN_HEIGHT || py <= 0)
		return (true);
	if (map[x][y] == '1')
		return (true);
	return (false);
}

void	draw_ray(t_game *game, double angle)
{
	double		ray_x;
	double		ray_y;
	t_player	*player;

	player = game->player;
	ray_x = player->pos_x;
	ray_y = player->pos_y;
	while (!touch(ray_x, ray_y, map))
	{
		pixel_put(game->img, ray_x, ray_y, 0xFF0000);
		ray_x += cos(angle);
		ray_y += sin(angle);
	}
}

void	raycasting(t_game *game)
{
	t_player	*player;
	t_ray		ray;
	double		dirX;
	double		dirY;
	int			i;
	double		cameraX;
	int			mapX;
	int			mapY;
	double		rayDirX;
	double		rayDirY;
	double		halfPlaneWidth;
	int			stepX;
	int			stepY;

	init_ray(&ray);
	game->ray = ray;
	halfPlaneWidth = tan(FOV * PI / 360.0);
	player = game->player;
	double sideDistX, sideDistY;
	double deltaDistX, deltaDistY;
	double planeX, planeY;
	dirY = 0;
	dirX = -1;
	i = 0;
	mapX = (int)player->pos_x;
	mapY = (int)player->pos_y;
	// printf("X : %f\nY : %f\n", player->pos_x, player->pos_y);
	// printf("posX : %d\nposY : %d\n", mapX, mapY);
	planeX = -player->dir_y * halfPlaneWidth;
	planeY = player->dir_x * halfPlaneWidth;
	while (i < WIN_WIDTH)
	{
		cameraX = 2 * i / (double)WIN_WIDTH - 1;
		rayDirX = player->dir_x + planeX * cameraX;
		rayDirY = player->dir_y + planeY * cameraX;
		// printf("dirX : %f\ndirY : %f\n", rayDirX, rayDirY);
		if (rayDirX != 0 && rayDirY != 0)
		{
			deltaDistX = fabs(1 / rayDirX);
			deltaDistY = fabs(1 / rayDirY);
		}
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player->pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player->pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player->pos_y) * deltaDistY;
		}
		while (!touch(mapX, mapY, map))
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				ray.side = X;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				ray.side = Y;
			}
		}
		printf("distX : %f\ndistY : %f\n", sideDistX - deltaDistX, sideDistY
			- deltaDistY);
		i++;
	}
}

int	render(t_game *game)
{
	t_player	*player;

	player = game->player;
	rotate_player(player);
	clear(game);
	draw_square(game->player->pos_x, game->player->pos_y, 10, game->img);
	draw_map(map, game->img);
	draw_ray(game, player->angle);
	raycasting(game);
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
	mlx_hook(game->win_ptr, DestroyNotify, NoEventMask, close_game, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, key_press, game->player);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_loop_hook(game->mlx_ptr, render, game);
	mlx_loop(game->mlx_ptr);
}
