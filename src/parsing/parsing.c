/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:09:01 by aubertra          #+#    #+#             */
/*   Updated: 2025/03/08 11:18:56 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*Utils for parsing_texture*/
int	format_check(char *line)
{
	int	pos;

	pos = 0;
	while (line[pos] && is_space(line[pos]))
		pos++;
	pos += 2;
	while (line[pos] && is_space(line[pos]))
		pos++;
	if (!(line[pos] == '.' && line[pos + 1] == '/'))
		return (error_msg(3));
	return (pos);
}

/*Displaying the correct error message*/
int	error_msg(int error_code)
{
	char	*msg;

	write(STDERR_FILENO, "Error\n", 6);
	if (error_code == 0)
		msg = "Program needs one argument\n";
	else if (error_code == 1)
		msg = "Program needs a configuration FILE .cub as argument\n";
	else if (error_code == 2)
		msg = "Configuration file cannot be opened, check permission\n";
	else if (error_code == 3)
		msg = "Texture needs to be given in this format: identifier ./file\n";
	else if (error_code == 4)
		msg = "Configuration file needs to include FIRST 4 textures and"
			" 2 color and THEN 1 map description ONLY\n";
	else if (error_code == 5)
		msg = "Texture file cannot be opened\n";
	else if (error_code == 6)
		msg = "Malloc issue\n";
	else if (error_code == 7)
		msg = "Colors needs to respect this format: identifier R, G, B with"
			" R, G and B between 0 and 255\n";
	else if (error_code == 8)
		msg = "Texture needs to be a .xpm file (not a directory)\n";
	write(STDERR_FILENO, msg, ft_strlen(msg));
	return (-1);
}

/*Checking that there is only one argument ending with .cub & opens it*/
int	arg_parsing(int argc, char **argv)
{
	int	len;
	int	fd_config;

	if (argc != 2)
		return (error_msg(0));
	len = ft_strlen(argv[1]);
	if (!(argv[1][len - 1] == 'b' && argv[1][len - 2] == 'u' && argv[1][len
			- 3] == 'c' && argv[1][len - 4] == '.'))
		return (error_msg(1));
	fd_config = open(argv[1], __O_DIRECTORY);
	if (fd_config != -1)
		return (close(fd_config), error_msg(1));
	fd_config = open(argv[1], O_RDONLY);
	if (fd_config == -1)
		return (error_msg(2));
	return (fd_config);
}

/*Content of the loop in parsing, will parse only texture and colors using gnl
on the whole document*/
int	parsing_text_col(int fd_config, int *done_text, int *done_col, t_game *game)
{
	char	*line;
	int		id;
	int		placeholder;

	line = get_next_line(fd_config);
	placeholder = 0;
	if (!line)
		return (close(fd_config), -1);
	if (*done_col > -1 && *done_text > -1 && is_texture(line, &id)
		&& parse_texture(line, done_text, id, game))
		*done_text = -1;
	if (*done_text > -1 && *done_col > -1 && is_color(line, &id)
		&& parse_color(line, done_col, id, game))
		*done_col = -1;
	if (*done_text < 4 && *done_col < 2
		&& is_map(line, &placeholder, game) == 1)
	{
		*done_col = -2;
		*done_text = -2;
	}
	free(line);
	return (0);
}

/*Main parsing function -> A COUPER EN 2*/
int	parsing(int argc, char **argv, t_game *game)
{
	int	fd_config;
	int	done_text;
	int	done_col;

	fd_config = arg_parsing(argc, argv);
	if (fd_config == -1)
		return (-1);
	done_text = 0;
	done_col = 0;
	while (1)
	{
		if (parsing_text_col(fd_config, &done_text, &done_col, game))
			break ;
	}
	if (done_text != 4 || done_col != 2)
		return (error_msg(4));
	if (parse_map(argv[1], fd_config, game) == -1)
		return (close(fd_config), -1);
	close(fd_config);
	return (0);
}
