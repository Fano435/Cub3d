/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:37:18 by jrasamim          #+#    #+#             */
/*   Updated: 2025/02/25 14:59:31 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_img(t_game *game)
{
	game->img = malloc(sizeof(t_img));
	game->img->mlx_img = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	game->img->addr = mlx_get_data_addr(game->img->mlx_img,
			&game->img->bits_per_pixel, &game->img->line_len,
			&game->img->endian);
	game->img_text_e = malloc(sizeof(t_img));
	game->img_text_e->mlx_img = NULL;
	game->img_text_e->addr = NULL;
	game->img_text_e->path = NULL;
	game->img_text_s = malloc(sizeof(t_img));
	game->img_text_s->mlx_img = NULL;
	game->img_text_s->addr = NULL;
	game->img_text_s->path = NULL;
	game->img_text_n = malloc(sizeof(t_img));
	game->img_text_n->mlx_img = NULL;
	game->img_text_n->addr = NULL;
	game->img_text_n->path = NULL;
	game->img_text_w = malloc(sizeof(t_img));
	game->img_text_w->mlx_img = NULL;
	game->img_text_w->addr = NULL;
	game->img_text_w->path = NULL;
}

void	init_mlx_textures(t_game *game)
{
	game->img_text_e->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->img_text_e->path, &game->img_text_e->width,
			&game->img_text_e->height);
	game->img_text_e->addr = mlx_get_data_addr(game->img_text_e->mlx_img,
			&game->img_text_e->bits_per_pixel, &game->img_text_e->line_len,
			&game->img_text_e->endian);
	game->img_text_n->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->img_text_n->path, &game->img_text_n->width,
			&game->img_text_n->height);
	game->img_text_n->addr = mlx_get_data_addr(game->img_text_n->mlx_img,
			&game->img_text_n->bits_per_pixel, &game->img_text_n->line_len,
			&game->img_text_n->endian);
	game->img_text_s->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->img_text_s->path, &game->img_text_s->width,
			&game->img_text_s->height);
	game->img_text_s->addr = mlx_get_data_addr(game->img_text_s->mlx_img,
			&game->img_text_s->bits_per_pixel, &game->img_text_s->line_len,
			&game->img_text_e->endian);
	game->img_text_w->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->img_text_w->path, &game->img_text_w->width,
			&game->img_text_w->height);
	game->img_text_w->addr = mlx_get_data_addr(game->img_text_w->mlx_img,
			&game->img_text_w->bits_per_pixel, &game->img_text_w->line_len,
			&game->img_text_w->endian);
}

void	init(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	game->ray = malloc(sizeof(t_ray));
	init_player(game->player);
	game->mlx_ptr = mlx_init();
	init_img(game);
	game->floor_color = -1;
	game->ceiling_color = -1;
	game->map_height = -1;
	game->map_width = -1;
}

void	init_player(t_player *player)
{
	player->fov = (60 * M_PI) / 180;
	player->pos_x = -1;
	player->pos_y = -1;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->angle = -1;
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
