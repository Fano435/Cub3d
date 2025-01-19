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
	mlx_destroy_display(game->mlx_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
	return (0);
}

int	handle_keys(int keysym, t_game *game)
{
	if (keysym == KEY_ESC)
		close_game(game);
	return (0);
}
