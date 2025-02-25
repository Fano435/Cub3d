/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:17:48 by jrasamim          #+#    #+#             */
/*   Updated: 2025/02/19 16:53:49 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cast_rays(t_game *game)
{
	t_ray	*ray;
	int		i;

	ray = game->ray;
	i = 0;
	ray->angle = game->player->angle - M_PI / 6;
	while (i < WIN_WIDTH)
	{
		init_ray(ray);
		get_wall_distance(game, ray);
		// render_wall(game, ray, i);
		// render_floor_ceiling(game, ray, i);
		ray->angle += (double)game->player->fov / WIN_WIDTH;
		if (ray->angle > 2 * M_PI)
			ray->angle -= 2 * M_PI;
		i++;
	}
}
