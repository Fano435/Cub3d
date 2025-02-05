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
	// if going NORTH
	if (sin(angle) > 0)
	{
		h_y++;
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
		v_x++;
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
	// printf("Initial y : %d\n\n", h_y);
	// printf("Initial x : %f, Int x : %d\n\n", h_x, (int)h_x);
	// printf("Step x : %f, step y : %d\n\n", x_step, y_step);
	while (!touch((int)h_x, h_y + pixel))
	{
		h_x += x_step;
		h_y += y_step;
	}
	// printf("Horizontal hit x : %f, Horizontal hit y : %d\n", h_x, h_y);
	pixel_put(game->img, h_x * BLOCK, h_y * BLOCK, 0xFF0000);
	return (sqrt(pow(player->pos_x - h_x, 2) + pow(player->pos_y - h_y, 2)));
}

// Pour les angles suivants :
// - (x_step et y _step) = 1 <=> cos(angle) et sin(angle) > 0 ,
// le raycasting fonctionne.
// Pour les autres il y'a vraisemblablement des decalages
// Concretement la detection est bonne pour la direction NORD OUEST
// Il manque plus qu'a faire les autres mais ca m'avancera sur les textures du coup
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
	// printf("Initial x : %d\n\n", v_x);
	// printf("Step x : %d, step y : %f\n\n", x_step, y_step);
	while (!touch(v_x + pixel, (int)v_y))
	{
		v_x += x_step;
		v_y += y_step;
	}
	// printf("Vertical hit x : %d, Vertical hit y : %f\n", v_x, v_y);
	pixel_put(game->img, v_x * BLOCK, v_y * BLOCK, 0x0000FF);
	return (sqrt(pow(player->pos_x - v_x, 2) + pow(player->pos_y - v_y, 2)));
}

void	cast_rays(t_game *game)
{
	double	h_inter;
	double	v_inter;
	t_ray	*ray;
	int		i;

	// printf("Vertical intersection distance : %f\n",
	// 	get_vertical_intersections(game, game->player->angle));
	// printf("Horizontal intersection distance : %f\n",
	// 	get_horizontal_intersections(game, game->player->angle));
	// get_vertical_intersections(game, game->player->angle);
	// get_horizontal_intersections(game, game->player->angle);
	// return ;
	ray = game->ray;
	i = 0;
	ray->angle = game->player->angle - (1.0472 / 2);
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
		ray->angle += (double)game->player->fov / WIN_WIDTH;
		if (ray->angle > 2 * M_PI)
			ray->angle -= 2 * M_PI;
		i++;
		// printf("Angle : %f\n", ray->angle);
	}
}

void	render_wall(t_game *game, t_ray *ray, int pos)
{
	double	dist_proj_plane;

	dist_proj_plane = (WIN_WIDTH / 2) / tan(game->player->fov);
	if (ray->wall_dist < 0)
		ray->wall_dist = 0.1;
	// printf("Plane distance : %f\n", dist_proj_plane);
	ray->wall_dist *= cos(ray->angle - game->player->angle);
	ray->line_height = (1 / ray->wall_dist) * dist_proj_plane;
	if (ray->line_height > WIN_HEIGHT)
		ray->line_height = WIN_HEIGHT - 1;
	ray->draw_start = WIN_HEIGHT / 2 + ray->line_height / 2;
	ray->draw_end = WIN_HEIGHT / 2 - ray->line_height / 2;
	while (ray->draw_start > ray->draw_end)
	{
		if (ray->side == 1)
			pixel_put(game->img, pos, ray->draw_start, 0xFF0000);
		else
			pixel_put(game->img, pos, ray->draw_start, 0xAA0000);
		ray->draw_start--;
	}
}
