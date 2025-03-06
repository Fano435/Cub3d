/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:36:24 by jrasamim          #+#    #+#             */
/*   Updated: 2025/02/25 15:01:10 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	render_loop(t_game *game)
{
	game->img->mlx_img = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	game->img->addr = mlx_get_data_addr(game->img->mlx_img,
			&game->img->bits_per_pixel, &game->img->line_len,
			&game->img->endian);
	move_player(game, game->player);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img->mlx_img, 0,
		0);
	mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
	return (1);
}

void	free_game(t_game *game)
{
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	if (game->player)
		free(game->player);
	free(game->ray);
	free(game->img_text_n->path);
	free(game->img_text_e->path);
	free(game->img_text_s->path);
	free(game->img_text_w->path);
	free(game->img_text_n);
	free(game->img_text_e);
	free(game->img_text_s);
	free(game->img_text_w);
	free(game->img);
	free(game);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = ft_calloc(sizeof(t_game), 1);
	init(game);
	if (parsing(ac, av, game) == -1)
	{
		free_game(game);
		return (-1);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"Cub3D");
	init_mlx_textures(game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, key_press, game->player);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_loop_hook(game->mlx_ptr, render_loop, game);
	mlx_hook(game->win_ptr, DestroyNotify, NoEventMask, close_game, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}
