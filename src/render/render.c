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
		pixel_put(game->img, pos, y, get_pixel_color(game, ray, y));
		y--;
	}
}
