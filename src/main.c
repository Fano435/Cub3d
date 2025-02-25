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

void	clear(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			pixel_put(game->img, i, j, 0x000000);
			j++;
		}
		i++;
	}
}

int	render(t_game *game)
{
	move_player(game, game->player);
	clear(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img->mlx_img, 0,
		0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;
	int		i;

	i = 0;
	game = ft_calloc(sizeof(t_game), 1);
	init(game);
	if (parsing(ac, av, game) == -1)
	{
		mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		if (game->player)
			free(game->player);
		free(game->ray);
		free(game->img_text_n);
		free(game->img_text_e);
		free(game->img_text_s);
		free(game->img_text_w);
		free(game->img);
		free(game);
		return (-1);
	}
	// game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"Cub3D");
	init_mlx_textures(game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, key_press, game->player);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_loop_hook(game->mlx_ptr, render, game);
	mlx_hook(game->win_ptr, DestroyNotify, NoEventMask, close_game, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}
