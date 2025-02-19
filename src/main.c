/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:36:24 by jrasamim          #+#    #+#             */
/*   Updated: 2025/02/19 14:14:55 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*SWITCH WITH MAP GIVEN IN CONFIGUATION FILE*/
char	map[10][8] = {{'1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '0', '1',
		'0', '0', '0', '0', '1'}, {'1', '0', '1', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '0', '1'}, {'1', '0', '0', '0', '0', '1',
		'0', '1'}, {'1', '0', '1', '0', '0', '0', '0', '1'}, {'1', '0', '0',
		'0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '1', '0', '0', '1'},
		{'1', '0', '0', '1', '0', '0', '0', '1'}, {'1', '1', '1', '1', '1', '1',
		'1', '1'}};
/////////////////////////////////////////////

bool	touch(int x, int y)
{
	if (x > WIN_WIDTH / BLOCK || x < 0 || y > WIN_HEIGHT / BLOCK || y < 0)
		return (true);
	if (map[y][x] == '1')
		return (true);
	return (false);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x >= WIN_WIDTH || x < 0 || y >= WIN_HEIGHT || y < 0)
		return ;
	offset = (y * img->line_len + x * (img->bits_per_pixel / 8));
	pixel = img->addr + offset;
	*(int *)pixel = color;
}

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
	t_player	*player;

	player = game->player;
	rotate_player(player);
	clear(game);
	pixel_put(game->img, player->pos_x * BLOCK, player->pos_y * BLOCK,
		0xFFFF00);
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
	dprintf(STDERR_FILENO, "game init done\n");
	parsing(ac, av, game);
	dprintf(STDERR_FILENO, "end of parsing\n");
	return (0);
	mlx_hook(game->win_ptr, DestroyNotify, NoEventMask, close_game, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, key_press, game->player);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_loop_hook(game->mlx_ptr, render, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}
