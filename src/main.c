/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:36:24 by jrasamim          #+#    #+#             */
/*   Updated: 2025/01/16 17:36:25 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init(t_game *game)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	game->mlx_ptr = mlx;
	win = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	game->win_ptr = win;
}

int	rgb_to_int(int r, int g, int b)
{
	// return ((256 * 256 * r) + (256 * g) + (b));
	return ((r << 16) | (g << 8) | (b));
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	offset = (y * img->line_len + x * (img->bits_per_pixel / 8));
	pixel = img->addr + offset;
	*(int *)pixel = color;
}

// Juste pour tester le fonctionnement de mlx_pixel_put()
void	draw_test(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < 960)
	{
		j = 0;
		while (j < 135)
		{
			img_pixel_put(img, i, j, 0xFF0000);
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_game	*game;
	t_img	img;

	// if (ac == 4)
	// {
	// 	printf("%d\n", rgb_to_int(ft_atoi(av[1]), ft_atoi(av[2]),
	// 			ft_atoi(av[3])));
	// 	return (1);
	// }
	(void)ac, (void)av;
	game = malloc(sizeof(t_game));
	init(game);
	img.mlx_img = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	game->img = &img;
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bits_per_pixel,
			&img.line_len, &img.endian);
	draw_test(&img);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img.mlx_img, 0, 0);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, handle_keys, game);
	mlx_hook(game->win_ptr, DestroyNotify, NoEventMask, close_game, game);
	mlx_loop(game->mlx_ptr);
}
