/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:58:41 by jrasamim          #+#    #+#             */
/*   Updated: 2025/02/06 19:58:42 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_floor_ceiling(t_game *game, t_ray *ray, int pos)
{
	int	ceiling_pixel;
	int	floor_pixel;

	ceiling_pixel = ray->draw_start;
	floor_pixel = ray->draw_end;
	while (ceiling_pixel < WIN_HEIGHT)
	{
		pixel_put(game->img, pos, ceiling_pixel++, 0x00FFFF);
	}
	while (floor_pixel > 0)
	{
		pixel_put(game->img, pos, floor_pixel--, 0x0000FF);
	}
}
