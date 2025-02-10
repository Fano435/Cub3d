/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:09:01 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/10 14:42:29 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


/*Checking that there is only one argument ending with .cub & opens it*/
int arg_parsing(int argc, char **argv)
{
    int len;
    int fd_config;

    if (argc != 2)
        return (error_msg(0));
    len = ft_strlen(argv[1]);
    if (!(argv[1][len - 1] == 'b' && argv[1][len - 2] == 'u' && argv[1][len - 3] == 'c'
            && argv[1][len - 4] == '.'))
        return (error_msg(1));
    fd_config = open(argv[1], O_RDONLY);
    if (fd_config == -1)
        return (error_msg(3));
    return (fd_config);
}

/*Check the texture line for errors & opens it + put the fd in the struct*/
int parse_texture(char *line, int *done, int *id)
{
    int     pos;
    int     len;
    char    *texture_file;
    int     fd_texture;

    pos = 2;
    while (is_space(line[pos]))
        pos++;
    if (!(line[pos] == '.' && line[pos + 1] == '/'))
        return (error_msg(3));
    if (get_texture_file(&texture_file, line, pos))
        return (-1);
    dprintf(STDERR_FILENO, "texture file is %s", texture_file);
    fd_texture = open(texture_file, O_RDONLY);
    free(texture_file);
    if (fd_texture == -1)
        return (error_msg(5));
    *done++;
    return (0);
}

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
        {
            if (done != 7)
                error_msg(4);
            break;
        }
        dprintf(STDOUT_FILENO, "line is: %s", line);
        if (is_texture(line, &id) && parse_texture(line, &done, &id))
            return (-1);
        // if (is_color(line, &id) && parse_color(line, &done))
        //     return (-1);
        // if (is_map(line, &done) && parse_map(line, done))
            // return (-1);
        free(line);
    }
    close(fd_config);
    return (0);
}
