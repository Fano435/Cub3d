/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:55:13 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/19 15:06:09 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*Return the id corresponding to the color (floor or ceilling))*/
int is_color(char *line, int *id)
{
    int i;

    i = 0;
    while (is_space(line[i]))
        i++;
    *id = 0;
    if (!my_strncmp(&line[i], "F", ft_strlen("F")))
        *id = F;
    else if (!my_strncmp(&line[i], "C", ft_strlen("C")))
        *id = C;
    // dprintf(STDERR_FILENO, "at the end of is_color, identifier is %d\n", *id);
    return (*id);
}

/*get each R G B in int format*/
int get_color(char *line, int *pos, int first_nb)
{
    int color;

    if (first_nb)
    {
        while (line[*pos] && (is_space(line[*pos])))
            (*pos)++;
    }
    else
    {
        while (line[*pos] && (is_space(line[*pos]) || line[*pos] == ','))
            (*pos)++;
    }
    color = 0;
    while (line[*pos] && is_digit(line[*pos]))
    {
        color = color * 10 + (line[*pos] - '0');
        (*pos)++;
    }
    if (color < 0 || color > 255)
        return (-1);
    return (color);
}

/*Main function for parsing of the colors*/
int parse_color(char *line, int *done, int id, t_game *game)
{
    int red;
    int green;
    int blue;
    int pos;
    int converted_color;

    pos = 2;
    red = get_color(line, &pos, 1);
    green = get_color(line, &pos, 0);
    blue = get_color(line, &pos, 0);
    if (red < 0 || blue < 0 || green < 0)
        return (error_msg(7));
    while (line[pos])
    {
        if(!is_space(line[pos]))
            return (error_msg(7));
        pos++;
    }
    converted_color = (red << 16 | green << 8 | blue);
    if (id == C)
        game->ceiling_color = converted_color;
    else if (id == F)
        game->floor_color = converted_color;
    (*done)++;
    return (0);
}

