/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:27:48 by jrasamim          #+#    #+#             */
/*   Updated: 2025/02/19 16:45:06 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	touch(int x, int y, t_game *game)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)(x);
	grid_y = (int)(y);
	if (grid_x < 0 || grid_x >= game->map_width || grid_y < 0
		|| grid_y >= game->map_height)
		return (true);
	return (game->map[grid_y][grid_x] == '1');
}

void	handle_rotate(t_player *player)
{
	float	angle_speed;

	angle_speed = 0.02;
	if (player->rotate_l)
	{
		player->angle -= angle_speed;
		if (player->angle < 0)
			player->angle = 2 * M_PI;
	}
	if (player->rotate_r)
	{
		player->angle += angle_speed;
		if (player->angle > 2 * M_PI)
			player->angle = 0;
	}
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
}

void	handle_movement(t_player *player, double *next_x, double *next_y)
{
	double	speed;

	speed = 0.04;
	if (player->key_up)
	{
		(*next_x) += cos(player->angle) * speed;
		(*next_y) += sin(player->angle) * speed;
	}
	if (player->key_down)
	{
		(*next_x) -= cos(player->angle) * speed;
		(*next_y) -= sin(player->angle) * speed;
	}
	if (player->key_right)
	{
		(*next_x) -= sin(player->angle) * speed;
		(*next_y) += cos(player->angle) * speed;
	}
	if (player->key_left)
	{
		(*next_x) += sin(player->angle) * speed;
		(*next_y) -= cos(player->angle) * speed;
	}
}

int	will_colide(t_game *game, double x, double y)
{
	float	radius;

	radius = 0.20;
	if (touch(x + radius, y + radius, game))
		return (1);
	else if (touch(x - radius, y - radius, game))
		return (1);
	else if (touch(x + radius, y - radius, game))
		return (1);
	else if (touch(x - radius, y + radius, game))
		return (1);
	else if (touch(x + radius, y, game))
		return (1);
	else if (touch(x - radius, y, game))
		return (1);
	else if (touch(x, y + radius, game))
		return (1);
	else if (touch(x, y - radius, game))
		return (1);
	return (0);
}

void	move_player(t_game *game, t_player *player)
{
	double	next_x;
	double	next_y;

	next_x = player->pos_x;
	next_y = player->pos_y;
	handle_rotate(player);
	handle_movement(player, &next_x, &next_y);
	if (!will_colide(game, next_x, next_y))
	{
		player->pos_x = next_x;
		player->pos_y = next_y;
	}
}
