/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:37:18 by jrasamim          #+#    #+#             */
/*   Updated: 2025/02/19 16:31:03 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init(t_game *game)
{
	void	*win;

	game->img = malloc(sizeof(t_img)); 
	//malloc for the textures
	game->img_text_n = malloc(sizeof(t_img));
	game->img_text_s = malloc(sizeof(t_img));
	game->img_text_e = malloc(sizeof(t_img));
	game->img_text_w = malloc(sizeof(t_img));
	//until here
	game->player = malloc(sizeof(t_player));
	game->ray = malloc(sizeof(t_ray));
	init_player(game->player);
	game->mlx_ptr = mlx_init();
	win = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	game->win_ptr = win;
	game->img->mlx_img = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	game->img->addr = mlx_get_data_addr(game->img->mlx_img,
			&game->img->bits_per_pixel, &game->img->line_len,
			&game->img->endian);
	game->floor_color = -1; //to update while parsing colors
	game->ceiling_color = -1; //to update while parsing colors
}

void	init_player(t_player *player)
{
	player->fov = (60 * M_PI) / 180; //pb ici ????
	player->pos_x = -1; //player pos to update in the map
	player->pos_y = -1; //player pos to update in the map
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->angle = -1; //to update depending on NSEW orientation
	player->key_up = false;
	player->key_right = false;
	player->key_down = false;
	player->key_left = false;
	player->rotate_l = false;
	player->rotate_r = false;
}

void	init_ray(t_ray *ray)
{
	ray->wall_dist = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	ray->side = 0;
}
