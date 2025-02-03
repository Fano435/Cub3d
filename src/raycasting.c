/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:17:48 by jrasamim          #+#    #+#             */
/*   Updated: 2025/02/03 17:18:35 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_horizontal_intersections(t_game *game, double angle)
{
	double		h_x;
	int			h_y;
	double		x_step;
	int			y_step;
	t_player	*player;

	player = game->player;
	y_step = 1;
	x_step = 1 / tan(angle);
	h_y = (int)player->pos_y;
	// if facing up
	if (sin(angle) < 0)
	{
		y_step *= -1;
		x_step *= -1;
	}
	else
		h_y++;
	h_x = player->pos_x + (h_y - player->pos_y) / tan(angle);
	while (!touch((int)h_x, h_y))
	{
		h_x += x_step;
		h_y += y_step;
		// pixel_put(game->img, h_x * BLOCK, h_y * BLOCK, 0xFF0000);
	}
	return (sqrt(pow(h_x, 2) + pow(h_y, 2)));
}

double	get_vertical_intersections(t_game *game, double angle)
{
	int			v_x;
	double		v_y;
	int			x_step;
	double		y_step;
	t_player	*player;

	player = game->player;
	x_step = 1;
	y_step = tan(angle);
	v_x = (int)player->pos_y;
	// if facing left
	if (cos(angle) < 0)
	{
		x_step *= -1;
		y_step *= -1;
	}
	else
		v_x++;
	v_y = player->pos_y + (v_x - player->pos_x) * tan(angle);
	while (!touch(v_x, (int)v_y))
	{
		v_x += x_step;
		v_y += y_step;
		// pixel_put(game->img, v_x * BLOCK, v_y * BLOCK, 0x0000FF);
	}
	return (sqrt(pow(v_x, 2) + pow(v_y, 2)));
}

void	cast_rays(t_game *game)
{
	double h_inter;
	double v_inter;
	t_ray *ray;
	int i;

	ray = game->ray;
	i = 0;
	ray->angle = game->player->angle - (game->player->fov / 2);
	while (i < WIN_WIDTH)
	{
		init_ray(ray);
		v_inter = get_vertical_intersections(game, ray->angle);
		h_inter = get_horizontal_intersections(game, ray->angle);
		if (v_inter < h_inter)
		{
			ray->wall_dist = v_inter;
			ray->side = 1;
		}
		else
			ray->wall_dist = h_inter;
		// render_wall(game, ray, i);
		ray->angle += game->player->fov / WIN_WIDTH;
		if (ray->angle > 2 * M_PI)
			ray->angle = 0;
		i++;
	}
}