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

void	init_player(t_player *player)
{
	player->x = WIN_WIDTH / 4;
	player->y = WIN_HEIGHT / 4;
	player->key_up = false;
	player->key_right = false;
	player->key_down = false;
	player->key_left = false;
	player->rotate_l = false;
	player->rotate_r = false;
	player->angle = 0;
}

void	move_player(t_player *player)
{
	int		speed;
	float	angle_speed;

	angle_speed = 0.01;
	speed = 1;
	if (player->key_up)
		player->y -= speed;
	if (player->key_down)
		player->y += speed;
	if (player->key_right)
		player->x += speed;
	if (player->key_left)
		player->x -= speed;
	if (player->rotate_l)
	{
		player->angle += angle_speed;
		if (player->angle > 2 * PI)
			player->angle = 0;
	}
	if (player->rotate_r)
	{
		if (player->angle < 0)
			player->angle = 2 * PI;
		player->angle -= angle_speed;
	}
}
