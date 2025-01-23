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
	int		speed;
	float	angle_speed;

	speed = 1;
	angle_speed = 0.05;
	if (player->rotate_l)
	{
		player->angle -= angle_speed;
		if (player->angle < 0)
			player->angle = 2 * PI;
	}
	if (player->rotate_r)
	{
		player->angle += angle_speed;
		if (player->angle > 2 * PI)
			player->angle = 0;
	}
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	// if (player->key_up)
	// {
	// 	player->pos_x += cos(player->angle) * speed;
	// 	player->pos_y += sin(player->angle) * speed;
	// }
	// if (player->key_down)
	// {
	// 	player->pos_x -= cos(player->angle) * speed;
	// 	player->pos_y -= sin(player->angle) * speed;
	// }
	// if (player->key_right)
	// {
	// 	player->pos_x -= sin(player->angle) * speed;
	// 	player->pos_y += cos(player->angle) * speed;
	// }
	// if (player->key_left)
	// {
	// 	player->pos_x += sin(player->angle) * speed;
	// 	player->pos_y -= cos(player->angle) * speed;
	// }
	// printf("Angle : %f\nCos : %f\nSin : %f\n", player->angle,
	// 	cos(player->angle), sin(player->angle));
	// printf("PosX : %f\nPosY : %f\n", player->pos_x, player->pos_x);
}
