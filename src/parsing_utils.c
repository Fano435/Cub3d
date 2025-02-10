/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:49:01 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/10 14:26:42 by aubertra         ###   ########.fr       */
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
        msg = "Configuration file needs to include 4 texture, 2 color and 1 map description\n";
    else if (error_code == 5)
        msg = "Texture file cannot be opened\n";
    else if (error_code == 6)
        msg = "Malloc issue\n";
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

/*Return the id corresponding to the color (floor or ceilling))*/
int is_color(char *line, int *id)
{
    id = 0;
    if (!ft_strncmp(line, "F", ft_strlen("F")))
        id = F;
    else if (!ft_strncmp(line, "C", ft_strlen("C")))
        id = C;
    return (id);
}