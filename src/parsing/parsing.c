/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:09:01 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/19 15:15:08 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*Displaying the correct error message*/
int error_msg(int error_code)
{
    char    *msg;

    write(STDERR_FILENO, "Error\n", 6);
    if (error_code == 0)
        msg = "Program needs one argument\n";
    else if (error_code == 1)
        msg = "Program needs a configuration file as argument\n";
    else if (error_code == 2)
        msg = "Configuration file cannot be opened, check permission\n";
    else if (error_code == 3)
        msg = "Texture needs to be given in this format: identifier ./file\n";
    else if (error_code == 4)
        msg = "Configuration file needs to include FIRST 4 textures and 2 color and\
                 THEN 1 map description ONLY\n";
    else if (error_code == 5)
        msg = "Texture file cannot be opened\n";
    else if (error_code == 6)
        msg = "Malloc issue\n";
    else if (error_code == 7)
        msg = "Colors needs to respect this format: identifier R, G, B with\
                 R, G and B between 0 and 255\n";
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
	if (!(argv[1][len - 1] == 'b' && argv[1][len - 2] == 'u'
		&& argv[1][len - 3] == 'c' && argv[1][len - 4] == '.'))
		return (error_msg(1));
	fd_config = open(argv[1], O_RDONLY);
	if (fd_config == -1)
		return (error_msg(3));
	return (fd_config);
}

/*Main parsing function -> A COUPER EN 2*/
int     parsing(int argc, char **argv, t_game *game)
{
    char    *line;
    int     fd_config;
    int     done;
    int     id;

    fd_config = arg_parsing(argc, argv);
    if (fd_config == -1)
        return (-1);
    done = 0;
    while (1)
    {
        line = get_next_line(fd_config);
        if (!line)
            break;
        // dprintf(STDOUT_FILENO, "line is: %s", line);
        if (is_texture(line, &id) && parse_texture(line, &done, id, game))
            return (-1);
        if (is_color(line, &id) && parse_color(line, &done, id, game))
            return (-1);
        free(line);
    }
    if (parse_map(argv[1], done, fd_config))
            return (-1);
    return (0);
}
