/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:37:18 by jrasamim          #+#    #+#             */
/*   Updated: 2025/03/07 14:37:22 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int		init_img(t_game *game)
{
	if (malloc_img(game))
		return (-1);
	game->img_text_e->mlx_img = NULL;
	game->img_text_e->addr = NULL;
	game->img_text_e->path = NULL;
	game->img_text_s->mlx_img = NULL;
	game->img_text_s->addr = NULL;
	game->img_text_s->path = NULL;
	game->img_text_n->mlx_img = NULL;
	game->img_text_n->addr = NULL;
	game->img_text_n->path = NULL;
	game->img_text_w->mlx_img = NULL;
	game->img_text_w->addr = NULL;
	game->img_text_w->path = NULL;
	return (0);
}

int	init_mlx_textures(t_game *game)
{
	if (init_mlx_img(game))
		return (-1);
	game->img_text_e->addr = mlx_get_data_addr(game->img_text_e->mlx_img,
			&game->img_text_e->bits_per_pixel, &game->img_text_e->line_len,
			&game->img_text_e->endian);
	if (!game->img_text_e->addr)
			return(error_msg_mlx(1));
	game->img_text_n->addr = mlx_get_data_addr(game->img_text_n->mlx_img,
			&game->img_text_n->bits_per_pixel, &game->img_text_n->line_len,
			&game->img_text_n->endian);
	if (!game->img_text_e->addr)
			return(error_msg_mlx(1));
	game->img_text_s->addr = mlx_get_data_addr(game->img_text_s->mlx_img,
			&game->img_text_s->bits_per_pixel, &game->img_text_s->line_len,
			&game->img_text_e->endian);
	if (!game->img_text_s->addr)
			return(error_msg_mlx(1));
	game->img_text_w->addr = mlx_get_data_addr(game->img_text_w->mlx_img,
			&game->img_text_w->bits_per_pixel, &game->img_text_w->line_len,
			&game->img_text_w->endian);
	if (!game->img_text_s->addr)
			return(error_msg_mlx(1));
	return (0);
}

int		init(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (error_msg(6));
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
		return (error_msg(6));
	init_player(game->player);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (error_msg_mlx(2));
	if (init_img(game))
		return (-1);
	game->floor_color = -1;
	game->ceiling_color = -1;
	game->map_height = -1;
	game->map_width = -1;
	return (0);
}

int		init_player(t_player *player)
{
	player->fov = (60.0 * M_PI) / 180.0;
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
	return (0);
}

int	init_ray(t_ray *ray)
{
	ray->wall_dist = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	ray->side = 0;
	return (0);
}
