/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:49:01 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/10 17:55:58 by aubertra         ###   ########.fr       */
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
        msg = "Configuration file needs to include 4 texture, 2 color and\
                 1 map description\n";
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

/*Return the id corresponding to the texture*/
int is_texture(char *line, int *id)
{
    id = 0;
    if (!ft_strncmp(line, "NO", ft_strlen("NO")))
        id = NO;
    else if (!ft_strncmp(line, "SO", ft_strlen("SO")))
        id = SO;
    else if (!ft_strncmp(line, "WE", ft_strlen("WE")))
        id = WE;
    else if (!ft_strncmp(line, "EA", ft_strlen("EA")))
        id = EA;
    return (id);
}

/*Check is char is a space*/
int is_space(char *c)
{
    if (c >= 9 && c <= 13 || c == 32)
        return (1);
    return (0);
}

/*Check is char is a space*/
int is_digit(char *c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

/*Get the texture file*/
int get_texture_file(char **texture_file, char *line, int pos)
{
    char    *texture_file;
    int     len;

    len = 0;
    while (line[pos + len] && !is_space(line[pos + len]))
        len++;
    *texture_file = (char *)malloc(sizeof(char) * (len + 1));
    if (*texture_file)
        return (error_msg(6));
    len = 0;
    while (line[pos + len])
    {
        *texture_file[pos] = line[pos + len];
        len++;
    }
    texture_file[pos] = '\0';
    return (0);
}
