/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:55:13 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/11 10:41:28 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*Return the id corresponding to the color (floor or ceilling))*/
int is_color(char *line, int *id)
{
    *id = 0;
    if (!my_strncmp(line, "F", ft_strlen("F")))
        *id = F;
    else if (!my_strncmp(line, "C", ft_strlen("C")))
        *id = C;
    dprintf(STDERR_FILENO, "at the end of is_color, identifier is %d\n", *id);
    return (*id);
}

/*get each R G B in int format*/
int get_color(char *line, int pos, int first_nb)
{
    int color;

    if (first_nb)
    {
        while (line[pos] && (is_space(line[pos])))
            pos++;
    }
    else
    {
        while (line[pos] && (is_space(line[pos]) || line[pos] == ','))
            pos++;
    }
    color = 0;
    while (line[pos] && is_digit(line[pos]))
    {
        color = color * 10 + (line[pos] - '0');
        pos++;
    }
    return (color);
}


/*Main function for parsing of the colors*/
int parse_color(char *line, int *done, int *id)
{
    int red;
    int green;
    int blue;
    int pos;
    int converted_color;

    pos = 2;
    red = get_color(line, pos, 1);
    green = get_color(line, pos, 0);
    blue = get_color(line, pos, 0);
    if (red < 0 || red > 255 || blue < 0 || blue > 255
        || green < 0 || green > 255)
        return (error_msg(7));
    while (line[pos])
    {
        if(!is_space(line[pos]))
            return (error_msg(7));
    }
    converted_color = (red << 16 | green << 8 | blue);
    dprintf(STDERR_FILENO, "converted color is %d\n", converted_color);
    //RESTE A ADD DANS LA BONNE STRUCTURE AU BON ENDROIT
    (void)id;
    (*done)++;
    return (0);
}
