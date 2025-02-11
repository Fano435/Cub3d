/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:49:01 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/11 11:23:41 by aubertra         ###   ########.fr       */
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
                 THEN 1 map description\n";
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
    *id = 0;
    if (!my_strncmp(line, "NO", ft_strlen("NO")))
        *id = NO;
    else if (!my_strncmp(line, "SO", ft_strlen("SO")))
        *id = SO;
    else if (!my_strncmp(line, "WE", ft_strlen("WE")))
        *id = WE;
    else if (!my_strncmp(line, "EA", ft_strlen("EA")))
        *id = EA;
    dprintf(STDERR_FILENO, "at the end of is_texture, identifier is %d\n", *id);
    return (*id);
}

/*Get the texture file*/
int get_texture_file(char **texture_file, char *line, int pos)
{
    int     len;

    len = 0;
    while (line[pos + len] && !is_space(line[pos + len]))
        len++;
    *texture_file = (char *)malloc(sizeof(char) * (len + 1));
    if (!(*texture_file))
        return (error_msg(6));
    while (line[pos + len])
    {
        if (!is_space(line[pos + len]))
            return (error_msg(3));
        len++;
    }
    len = 0;
    while (line[pos + len] && !is_space(line[pos + len]))
    {
        (*texture_file)[len] = line[pos + len];
        len++;
    }
    (*texture_file)[len] = '\0';
    return (0);
}
