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
	// Remplacer x par map_width une fois qu'il sera recupere
	if (x > 29 || x <= 0 || y >= game->map_height || y <= 0)
		return (true);
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

void	handle_rotate(t_player *player)
{
	float	angle_speed;

	angle_speed = 0.01;
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

	speed = 0.01;
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

int	will_colide(t_game *game, t_player *player, double x, double y)
{
	if (player->pos_x != (int)x && player->pos_y != (int)y)
	{
		if (touch(player->pos_x, (int)y, game))
			return (1);
		if (touch((int)x, player->pos_y, game))
			return (1);
	}
	return (touch((int)x, (int)y, game));
}

void	move_player(t_game *game, t_player *player)
{
	double	next_x;
	double	next_y;

	next_x = player->pos_x;
	next_y = player->pos_y;
	handle_rotate(player);
	handle_movement(player, &next_x, &next_y);
	if (!will_colide(game, player, next_x, next_y))
	{
		player->pos_x = next_x;
		player->pos_y = next_y;
	}
	// printf("PosX : %f\nPosY : %f\n", player->pos_x, player->pos_y);
}
