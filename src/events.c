/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:00:24 by jrasamim          #+#    #+#             */
/*   Updated: 2025/01/17 17:00:25 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	if (game->img)
		free(game->img);
	if (game->player)
		free(game->player);
	free(game);
	return (0);
}

int	key_press(int keysym, t_player *player)
{
	if (keysym == W)
		player->key_up = true;
	else if (keysym == D)
		player->key_right = true;
	else if (keysym == S)
		player->key_down = true;
	else if (keysym == A)
		player->key_left = true;
	else if (keysym == A)
		player->key_left = true;
	else if (keysym == LEFT)
		player->rotate_l = true;
	else if (keysym == RIGHT)
		player->rotate_r = true;
	return (0);
}

int	key_release(int keysym, t_game *game)
{
	t_player	*player;

	player = game->player;
	if (keysym == W)
		player->key_up = false;
	else if (keysym == D)
		player->key_right = false;
	else if (keysym == S)
		player->key_down = false;
	else if (keysym == A)
		player->key_left = false;
	else if (keysym == LEFT)
		player->rotate_l = false;
	else if (keysym == RIGHT)
		player->rotate_r = false;
	if (keysym == KEY_ESC)
		close_game(game);
	return (0);
}
