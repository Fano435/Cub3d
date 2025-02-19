/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:38:39 by jrasamim          #+#    #+#             */
/*   Updated: 2025/02/19 14:37:18 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_img	get_texture_img(t_game *game, t_ray *ray)
{
	// Si le rayon rencontre un mur vertical
	if (ray->side)
	{
		if (cos(ray->angle) > 0)
			return (*(game->img_text_e));
		else
			return (*(game->img_text_w));
	}
	else
	{
		if (sin(ray->angle) > 0)
			return (*(game->img_text_s));
		else
			return (*(game->img_text_n));
	}
}

double	get_pixel_x(t_img texture, t_ray *ray)
{
	double	x;

	if (ray->side)
		x = fmod(ray->vertical_hit, 1.0) * texture.width;
	else
		x = fmod(ray->horizontal_hit, 1.0) * texture.width;
	return (x);
}

int	pixel_get(t_img *texture, double x, double y)
{
	char	*pixel;

	pixel = texture->addr + ((int)y * texture->line_len + (int)x
			* (texture->bits_per_pixel / 8));
	return (*(int *)pixel);
}

int	get_pixel_color(t_game *game, t_ray *ray, int y)
{
	t_img	texture;
	int		color;
	double	pixel_x;
	double	pixel_y;

	color = 0x00000000;
	texture = get_texture_img(game, ray);
	if (!texture.path)
		return (color);
	if (!texture.addr)
	{
		texture.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, texture.path,
				&texture.width, &texture.height);
		texture.addr = mlx_get_data_addr(texture.mlx_img,
				&texture.bits_per_pixel, &texture.line_len, &texture.endian);
	}
	pixel_x = get_pixel_x(texture, ray);
	pixel_y = (y * 1.0 / WIN_HEIGHT) * texture.height;
	color = pixel_get(&texture, pixel_x, pixel_y);
	// printf("Text width %d, Text height %d Text x : %f, Text y :%f, y :%d\n",
	// 	texture.width, texture.height, pixel_x, pixel_y, y);
	// printf("Color : %d\n", color);
	return (color);
}
