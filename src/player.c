/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:27:48 by jrasamim          #+#    #+#             */
/*   Updated: 2025/01/21 14:27:50 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_player(t_player *player)
{
	double	speed;
	float	angle_speed;
	double	next_x;
	double	next_y;

	speed = 0.008;
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
	next_x = player->pos_x;
	next_y = player->pos_y;
	if (player->key_up)
	{
		next_x += cos(player->angle) * speed;
		next_y += sin(player->angle) * speed;
	}
	if (player->key_down)
	{
		next_x -= cos(player->angle) * speed;
		next_y -= sin(player->angle) * speed;
	}
	if (player->key_right)
	{
		next_x -= sin(player->angle) * speed;
		next_y += cos(player->angle) * speed;
	}
	if (player->key_left)
	{
		next_x += sin(player->angle) * speed;
		next_y -= cos(player->angle) * speed;
	}
	if (!touch((int)(next_x), (int)(next_y)))
	{
		player->pos_x = next_x;
		player->pos_y = next_y;
	}
	// printf("Angle : %f\nCos : %f\nSin : %f\n", player->angle,
	// 	cos(player->angle), sin(player->angle));
	// printf("PosX : %f\nPosY : %f\n", player->pos_x, next_y);
}
