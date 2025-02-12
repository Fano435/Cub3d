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

int	h_check(double angle, int *h_y, int *step)
{
	// if going SOUTH
	if (sin(angle) > 0)
	{
		(*h_y)++;
		return (0);
	}
	*step *= -1;
	return (-1);
}

int	v_check(double angle, int *v_x, int *step)
{
	// if going EAST
	if (cos(angle) > 0)
	{
		(*v_x)++;
		return (0);
	}
	*step *= -1;
	return (-1);
}

double	get_horizontal_intersections(t_game *game, double angle)
{
	double		h_x;
	int			h_y;
	double		x_step;
	int			y_step;
	int			pixel;
	t_player	*player;

	player = game->player;
	y_step = 1;
	h_y = (int)player->pos_y;
	pixel = h_check(angle, &h_y, &y_step);
	x_step = y_step / tan(angle);
	h_x = player->pos_x + (h_y - player->pos_y) / tan(angle);
	while (!touch((int)h_x, h_y + pixel))
	{
		h_x += x_step;
		h_y += y_step;
	}
	game->ray->horizontal_hit = h_x;
	return (sqrt(pow(player->pos_x - h_x, 2) + pow(player->pos_y - h_y, 2)));
}

double	get_vertical_intersections(t_game *game, double angle)
{
	int			v_x;
	double		v_y;
	int			x_step;
	double		y_step;
	int			pixel;
	t_player	*player;

	player = game->player;
	x_step = 1;
	v_x = (int)player->pos_x;
	pixel = v_check(angle, &v_x, &x_step);
	y_step = x_step * tan(angle);
	v_y = player->pos_y + (v_x - player->pos_x) * tan(angle);
	while (!touch(v_x + pixel, (int)v_y))
	{
		v_x += x_step;
		v_y += y_step;
	}
	game->ray->vertical_hit = v_y;
	return (sqrt(pow(player->pos_x - v_x, 2) + pow(player->pos_y - v_y, 2)));
}

void	cast_rays(t_game *game)
{
	double	h_inter;
	double	v_inter;
	t_ray	*ray;
	int		i;

	ray = game->ray;
	i = 0;
	ray->angle = game->player->angle - M_PI / 6;
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
		render_wall(game, ray, i);
		render_floor_ceiling(game, ray, i);
		ray->angle += (double)game->player->fov / WIN_WIDTH;
		if (ray->angle > 2 * M_PI)
			ray->angle -= 2 * M_PI;
		i++;
	}
}
