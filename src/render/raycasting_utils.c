/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:06:32 by jrasamim          #+#    #+#             */
/*   Updated: 2025/02/25 15:06:33 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	h_check(double angle, double *h_y, double *step)
{
	if (sin(angle) > 0)
	{
		(*h_y)++;
		return (0);
	}
	*step *= -1;
	return (-1);
}

int	v_check(double angle, double *v_x, double *step)
{
	if (cos(angle) > 0)
	{
		(*v_x) += 1;
		return (0);
	}
	*step *= -1;
	return (-1);
}

double	get_horizontal_intersections(t_game *game, double angle)
{
	double	h_x;
	double	h_y;
	double	x_step;
	double	y_step;
	int		pixel;

	y_step = 1;
	h_y = floor(game->player->pos_y);
	pixel = h_check(angle, &h_y, &y_step);
	x_step = y_step / tan(angle);
	h_x = game->player->pos_x + (h_y - game->player->pos_y) / tan(angle);
	while (!touch(h_x, h_y + pixel, game))
	{
		h_x += x_step;
		h_y += y_step;
	}
	game->ray->horizontal_hit = h_x;
	return (sqrt(pow(h_x - game->player->pos_x, 2) + pow(h_y
				- game->player->pos_y, 2)));
}

double	get_vertical_intersections(t_game *game, double angle)
{
	double	v_x;
	double	v_y;
	double	x_step;
	double	y_step;
	int		pixel;

	x_step = 1;
	v_x = floor(game->player->pos_x);
	pixel = v_check(angle, &v_x, &x_step);
	y_step = x_step * tan(angle);
	v_y = game->player->pos_y + (v_x - game->player->pos_x) * tan(angle);
	while (!touch(v_x + pixel, v_y, game))
	{
		v_x += x_step;
		v_y += y_step;
	}
	game->ray->vertical_hit = v_y;
	return (sqrt(pow(v_x - game->player->pos_x, 2) + pow(v_y
				- game->player->pos_y, 2)));
}

void	get_wall_distance(t_game *game, t_ray *ray)
{
	double	h_inter;
	double	v_inter;

	v_inter = get_vertical_intersections(game, ray->angle);
	h_inter = get_horizontal_intersections(game, ray->angle);
	if (v_inter < h_inter)
	{
		ray->side = 1;
		ray->wall_dist = v_inter;
	}
	else
		ray->wall_dist = h_inter;
}
