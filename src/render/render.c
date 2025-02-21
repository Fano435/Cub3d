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
	(void)pos;
	while (y > ray->draw_end)
	{
		// if (ray->side == 1)
		// 	pixel_put(game->img, pos, y, 0xFF0000);
		// else
		// 	pixel_put(game->img, pos, y, 0xAA0000);
		pixel_put(game->img, pos, y, get_pixel_color(game, ray, y));
		// get_pixel_color(game, ray, y);
		y--;
	}
}
