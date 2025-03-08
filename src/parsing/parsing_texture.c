/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:49:01 by aubertra          #+#    #+#             */
/*   Updated: 2025/03/08 11:17:36 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*Return the id corresponding to the texture*/
int	is_texture(char *line, int *id)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	*id = 0;
	if (!my_strncmp(&line[i], "NO", ft_strlen("NO")))
		*id = NO;
	else if (!my_strncmp(&line[i], "SO", ft_strlen("SO")))
		*id = SO;
	else if (!my_strncmp(&line[i], "WE", ft_strlen("WE")))
		*id = WE;
	else if (!my_strncmp(&line[i], "EA", ft_strlen("EA")))
		*id = EA;
	if (*id != 0 && (size_t)(i + 2) < ft_strlen(line) && !is_space(line[i + 2]))
		*id = -1;
	return (*id);
}

/*Get the texture file*/
int	get_texture_file(char **texture_file, char *line, int pos)
{
	int	len;

	len = 0;
	while (line[pos + len] && !is_space(line[pos + len]))
		len++;
	*texture_file = (char *)malloc(sizeof(char) * (len + 1));
	if (!(*texture_file))
		return (error_msg(6));
	while (line[pos + len])
	{
		if (!is_space(line[pos + len]))
			return (free(*texture_file), error_msg(3));
		len++;
	}
	len = 0;
	while (line[pos + len] && !is_space(line[pos + len]))
	{
		(*texture_file)[len] = line[pos + len];
		len++;
	}
	(*texture_file)[len] = '\0';
	if (!((*texture_file)[len - 1] == 'm' && (*texture_file)[len - 2] == 'p'
		&& (*texture_file)[len - 3] == 'x' && (*texture_file)[len - 4] == '.'))
		return (free(*texture_file), error_msg(8));
	return (0);
}

/*Adding the parsed texture to the appropriate 
variable of the game struct*/
int	add_text_to_game(char *texture_file, int id, t_game *game)
{
	t_img	*curr_text;

	if (id == NO)
		curr_text = game->img_text_n;
	else if (id == SO)
		curr_text = game->img_text_s;
	else if (id == WE)
		curr_text = game->img_text_w;
	else
		curr_text = game->img_text_e;
	if (curr_text->path)
		return (error_msg(4));
	curr_text->path = ft_strdup(texture_file);
	free(texture_file);
	return (0);
}

/*Check if the texture file permission and if it is a dir or a file*/
int	opening_check(char *texture_file)
{
	int		fd_texture;

	fd_texture = open(texture_file, __O_DIRECTORY);
	if (fd_texture != -1)
		return (error_msg(8));
	fd_texture = open(texture_file, O_RDONLY);
	if (fd_texture == -1)
		return (free(texture_file), error_msg(5));
	close(fd_texture);
	return (0);
}

/*Check the texture line for errors & try to opens it
+ put the file relative path in the struct*/
int	parse_texture(char *line, int *done_text, int id, t_game *game)
{
	int		pos;
	char	*texture_file;

	if (id == -1)
	{
		*done_text = -1;
		return (error_msg(3));
	}
	if (*done_text >= 4)
		return (-1);
	pos = format_check(line);
	if (pos == -1)
		return (-1);
	while (line[pos] && is_space(line[pos]))
		pos++;
	if (!(line[pos] == '.' && line[pos + 1] == '/'))
		return (error_msg(3));
	if (get_texture_file(&texture_file, line, pos))
		return (-1);
	if (opening_check(texture_file) == -1)
		return (free(texture_file), -1);
	if (add_text_to_game(texture_file, id, game))
		return (free(texture_file), -1);
	(*done_text)++;
	return (0);
}
