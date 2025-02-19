/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:09:01 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/19 11:31:38 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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

void	init_texture(char *path, int id, t_game *game)
{
	t_img	texture;

	texture.path = ft_strdup(path);
	texture.addr = NULL;
	texture.mlx_img = NULL;
	game->textures[id] = texture;
	printf("ID : %d, path : %s\n", id, texture.path);
}

/*Check the texture line for errors & try to opens it
+ put the file relative path in the struct*/
int	parse_texture(char *line, int *done, int id, t_game *game)
{
	int		pos;
	char	*texture_file;
	int		fd_texture;

	pos = 3;
	while (line[pos] && is_space(line[pos]))
		pos++;
	if (!(line[pos] == '.' && line[pos + 1] == '/'))
		return (error_msg(3));
	if (get_texture_file(&texture_file, line, pos))
	{
		dprintf(STDERR_FILENO, "get_texture_file error\n");
		return (-1);
	}
	dprintf(STDERR_FILENO, RED "texture file is %s\n" RESET, texture_file);
	fd_texture = open(texture_file, O_RDONLY);
	if (fd_texture == -1)
		return (error_msg(5));
	close(fd_texture);
	(*done)++;
	init_texture(texture_file, id, game);
	free(texture_file);
	return (0);
}

/*Main parsing function -> A COUPER EN 2*/
int     parsing(int argc, char **argv)
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
        if (is_texture(line, &id) && parse_texture(line, &done, &id))
        {
            dprintf(STDERR_FILENO, "Error while parsing textures\n");
            return (-1);
        }
        if (is_color(line, &id) && parse_color(line, &done, &id))
        {
            dprintf(STDERR_FILENO, "Error while parsing colors\n");
            return (-1);
        }
        free(line);
    }
    if (done > 6)
    {
        dprintf(STDERR_FILENO, "replace by error msg: too many colors or too many textures\n");
        return (-1);
    }
    if (parse_map(argv[1], done, fd_config))
            return (-1);
    close(fd_config);
    return (0);
}
