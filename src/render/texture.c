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

t_img	*get_texture_img(t_game *game, t_ray *ray)
{
	if (ray->side)
	{
		if (ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2)
			return ((game->img_text_e));
		else
			return ((game->img_text_w));
	}
	else
	{
		if (ray->angle > 0 && ray->angle < M_PI)
			return ((game->img_text_n));
		else
			return ((game->img_text_s));
	}
}

double	get_pixel_x(t_img texture, t_ray *ray)
{
	double	x;

	if (ray->side)
		x = (ray->vertical_hit - floor(ray->vertical_hit)) * texture.width;
	else
		x = (ray->horizontal_hit - floor(ray->horizontal_hit)) * texture.width;
	return (x);
}

int	pixel_get(t_img *texture, double x, double y)
{
	char	*pixel;

	pixel = texture->addr + ((int)y * texture->line_len + (int)x
			* (texture->bits_per_pixel / 8));
	return (*(int *)pixel);
}

int	get_pixel_color(t_game *game, t_ray *ray, double y)
{
	t_img	*texture;
	int		color;
	double	pixel_x;
	double	pixel_y;

	color = 0x00000000;
	texture = get_texture_img(game, ray);
	if (!texture->path)
		return (color);
	pixel_x = get_pixel_x(*texture, ray);
	pixel_y = ((y - ray->draw_end) * texture->height / ray->line_height);
	color = pixel_get(texture, pixel_x, pixel_y);
	return (color);
}
