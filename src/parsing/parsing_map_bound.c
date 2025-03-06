/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_bound.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:49:07 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/26 16:31:18 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*Usual flood fill*/
void	flood_fill(char **map, int x, int y, int height)
{
	if (x < 0 || y < 0 || x > ((int)ft_strlen(map[y]) - 1) || y > (height - 1)
		|| map[y][x] == '1' || is_space(map[y][x]) || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x - 1, y, height);
	flood_fill(map, x + 1, y, height);
	flood_fill(map, x, y - 1, height);
	flood_fill(map, x, y + 1, height);
}

/*Check the flooded map to make sure that the position filled
are not limits of the map or adjacent to spaces*/
int	check_flooded_map(char **map, int height)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'F' && (x == 0 || x == ((int)ft_strlen(map[y]) - 1)
					|| y == (height - 1) || y == 0 || is_space(map[y][x + 1])
					|| is_space(map[y][x - 1]) || is_space(map[y + 1][x])
					|| is_space(map[y - 1][x])))
				return (error_msg_map(2));
			x++;
		}
		y++;
	}
	return (1);
}

/*Main function to verify the converted map is correct*/
int	valid_map(t_game *game)
{
	int		x;
	int		y;
	char	**map_copy;

	x = game->player->pos_x;
	y = game->player->pos_y;
	map_copy = copy_map(game->map, game->map_height);
	flood_fill(map_copy, x, y, game->map_height);
	if (check_flooded_map(map_copy, game->map_height) == -1)
		return (free_map(map_copy), -1);
	free_map(map_copy);
	return (1);
}
