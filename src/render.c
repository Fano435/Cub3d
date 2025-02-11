/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:58:41 by jrasamim          #+#    #+#             */
/*   Updated: 2025/02/06 19:58:42 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_floor_ceiling(t_game *game, t_ray *ray, int pos)
{
	int	ceiling_pixel;
	int	floor_pixel;

	floor_pixel = ray->draw_start;
	ceiling_pixel = ray->draw_end;
	while (floor_pixel < WIN_HEIGHT)
	{
		pixel_put(game->img, pos, floor_pixel++, game->floor_color);
	}
	while (ceiling_pixel > 0)
	{
		pixel_put(game->img, pos, ceiling_pixel--, game->ceiling_color);
	}
}

t_img	get_texture_img(t_game *game, t_ray ray)
{
	// Si le rayon rencontre un mur vertical
	if (ray.side)
	{
		if (cos(ray.angle) > 0)
			return (game->textures[EA]);
		else
			return (game->textures[WE]);
	}
	else
	{
		if (sin(ray.angle) > 0)
			return (game->textures[SO]);
		else
			return (game->textures[NO]);
	}
}

double	get_pixel_x(t_img texture, t_ray ray)
{
	double	x;

	if (ray.side)
		x = fmod(ray.vertical_hit, 1.0) * texture.width;
	else
		x = fmod(ray.horizontal_hit, 1.0) * texture.width;
	return (x);
}

int	get_pixel_color(t_game *game, t_ray ray, int y)
{
	t_img	texture;
	int		color;
	int		pixel_x;
	int		pixel_y;

	color = 0x00000000;
	texture = get_texture_img(game, ray);
	texture.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, texture.path,
			&texture.width, &texture.height);
	texture.addr = mlx_get_data_addr(texture.mlx_img, &texture.bits_per_pixel,
			&texture.line_len, &texture.endian);
	pixel_x = (int)get_pixel_x(texture, ray);
	pixel_y = (int)(y * (WIN_HEIGHT / texture.height));
	printf("Texture x : %d, texture y : %d\n", pixel_x, pixel_y);
	return (color);
}

void	render_wall(t_game *game, t_ray *ray, int pos)
{
	double	dist_proj_plane;
	int		y;

	dist_proj_plane = (WIN_WIDTH / 2) / tan(game->player->fov);
	if (ray->wall_dist < 0)
		ray->wall_dist = 0.1;
	ray->line_height = (1 / ray->wall_dist) * dist_proj_plane;
	if (ray->line_height > WIN_HEIGHT)
		ray->line_height = WIN_HEIGHT - 1;
	ray->draw_start = WIN_HEIGHT / 2 + ray->line_height / 2;
	ray->draw_end = WIN_HEIGHT / 2 - ray->line_height / 2;
	y = ray->draw_start;
	while (y > ray->draw_end)
	{
		if (ray->side == 1)
			pixel_put(game->img, pos, y, 0xFF0000);
		else
			pixel_put(game->img, pos, y, 0xAA0000);
		get_pixel_color(game, *ray, y);
		y--;
	}
}
