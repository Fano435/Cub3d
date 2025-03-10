/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:16:25 by aubertra          #+#    #+#             */
/*   Updated: 2025/03/10 10:33:45 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Personnalized error message concerning the map*/
int	error_msg_map(int error_code)
{
	char	*msg;

	write(STDERR_FILENO, "Error\n", 6);
	if (error_code == 1)
		msg = "Map description should only contains 0 (floor),"
			" 1 (walls) and 1 player orientation indicator (N, S, E, W)\n";
	else if (error_code == 2)
		msg = "Map is not bound by walls\n";
	else if (error_code == 3)
		msg = "Map description cannot contain more than 1 starting"
			" position for the player\n";
	else if (error_code == 4)
		msg = "Map description could not be converted into array\n";
	else if (error_code == 5)
		msg = "No player starting position\n";
	write(STDERR_FILENO, msg, ft_strlen(msg));
	return (-1);
}

/*Display the map (DEBUG ONLY)*/
void	print_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		dprintf(STDERR_FILENO, "[");
		while (map[i][j])
		{
			dprintf(STDERR_FILENO, "%c", map[i][j]);
			j++;
		}
		dprintf(STDERR_FILENO, "]");
		dprintf(STDERR_FILENO, "\n");
		i++;
	}
}

/*Free the map at the end of the code*/
void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

/*copy the map into a new char ** to avoid changing the real map
when doing the flood fill check*/
char	**copy_map(char **original, int height)
{
	char	**copy;
	int		i;

	copy = (char **)malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(original[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

/*Adding the starting position and orientation of the player*/
int	add_pos_game(int x, int y, int found, t_game *game)
{
	char	orientation;

	if (!found)
		return (-1);
	game->player->pos_x = x + 0.5;
	game->player->pos_y = y + 0.5;
	orientation = game->map[y][x];
	if (orientation == 'N')
		game->player->angle = 3 * M_PI / 2;
	else if (orientation == 'S')
		game->player->angle = M_PI / 2;
	else if (orientation == 'E')
		game->player->angle = 0;
	else if (orientation == 'W')
		game->player->angle = M_PI;
	return (game->player->angle);
}
