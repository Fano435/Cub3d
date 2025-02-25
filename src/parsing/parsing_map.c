/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:16:25 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/25 15:12:38 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Check if the line is part of the map/contain only only 1, 0, spaces
and no more than one player position charater*/
int	is_map(char *line, int *player_pos, t_game *game)
{
	int	pos;
	int	id;

	pos = 0;
	if (is_color(line, &id) || is_texture(line, &id) || line[pos] == '\n')
		return (0);
	while (line[pos])
	{
		if (line[pos] != '1' && line[pos] != '0' && !is_space(line[pos])
			&& line[pos] != 'N' && line[pos] != 'S' && line[pos] != 'E'
			&& line[pos] != 'W')
			return (error_msg_map(1));
		if (player_pos && (line[pos] == 'N' || line[pos] == 'S'
				|| line[pos] == 'E' || line[pos] == 'W'))
			(*player_pos)++;
		if (player_pos && *player_pos > 1)
			return (error_msg_map(3));
		pos++;
	}
	if (game->map_width < pos)
		game->map_width = pos;
	return (1);
}

/*Get the heigh of the map to alloc the char **
& check that the map description contains ONLY authorized characters*/
int	get_height(int fd_config, t_game *game)
{
	int		height;
	int		ret_map;
	char	*line;
	int		player_pos;
	int		stop;

	height = 0;
	player_pos = 0;
	stop = 0;
	while (1)
	{
		line = get_next_line(fd_config);
		if (!line)
			break ;
		if (!stop)
			ret_map = is_map(line, &player_pos, game);
		if (ret_map == 1)
			height++;
		else if (ret_map == -1 || (height > 0 && !ret_map))
			stop = 1;
		free(line);
	}
	if (stop)
		return (-1);
	return (height);
}

/*Convert the map into a char ** to finish the parsing*/
char	**file_to_array(int fd_config, char *config_file, int height,
		t_game *game)
{
	char	**map;
	char	*line;
	int		i;

	close(fd_config);
	fd_config = open(config_file, O_RDONLY);
	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (error_msg(6), NULL);
	i = 0;
	while (1)
	{
		line = get_next_line(fd_config);
		if (!line)
			break ;
		if (is_map(line, NULL, game) == 1)
		{
			map[i] = my_strdup(line);
			i++;
		}
		free(line);
	}
	map[i] = NULL;
	return (map);
}

int	get_starting_pos(char **map, t_game *game)
{
	int	x;
	int	y;
	int	found;

	x = 0;
	y = 0;
	found = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'E'
				|| map[y][x] == 'S')
			{
				found = 1;
				break ;
			}
			x++;
		}
		if (found == 1)
			break ;
		y++;
	}
	return (add_pos_game(x, y, found, game));
}

/*Main fonction handling the parsing of the map*/
int	parse_map(char *config_file, int done, int fd_config, t_game *game)
{
	char	**map;
	int		height;

	if (done != 6)
		return (error_msg(4));
	close(fd_config);
	fd_config = open(config_file, O_RDONLY);
	height = get_height(fd_config, game);
	if (height < 1)
		return (-1);
	map = file_to_array(fd_config, config_file, height, game);
	if (!map)
		return (error_msg_map(4));
	game->map = map;
	game->map_height = height;
	if (get_starting_pos(map, game) == -1)
		return (-1);
	if (valid_map(height, game) == -1)
		return (-1);
	done++;
	close(fd_config);
	return (0);
}
