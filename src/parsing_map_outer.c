/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_outer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:49:07 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/18 15:01:01 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*Recursive check, depending on the side of the map that is checked, the function looks
for a wall*/
int valid_char(char **map, int line_p, int char_p, int id)
{
    dprintf(STDERR_FILENO, "line %d, char %d: '%c'\n", line_p, char_p, map[line_p][char_p]);
    if (map[line_p][char_p] == '1')
        return (1);
    else if (is_space(map[line_p][char_p]))
    {
        if (id == FIRST_COL)
            char_p++;
        else if (id == LAST_COL)
            char_p--;
        else if (id == FIRST_LINE)
            line_p++;
        else if (id == LAST_LINE)
            line_p--;
        return (valid_char_line(map, line_p, char_p, id));
    }
    else // == '0' or N S W E
        return (error_msg_map(2));
}

/*Check that outer lines are properly bounded*/
int valid_outer_line(char **map, int line_p, int id)
{
    int char_p;

    char_p = 0;
    while(map[line_p][char_p])
    {
        if (valid_char_line(map, line_p, char_p, id) == 1)
            char_p++;
        else if (valid_char_line(map, line_p, char_p, id) == -1)
            return (-1);
    }
    return (1);
}

/*Check that an outer column is properly bounded*/
int valid_col(char **map, int id)
{
    int char_p;
    int line_p;

    line_p = 0;
    char_p = 0;
    if (id == LAST_COL)
        char_p = my_strlen(map[line_p]);
    while(map[line_p][char_p])
    {
        if (valid_char(map, line_p, char_p, id) == 1)
        {
            line_p++;
            if (id == LAST_COL)
                char_p = my_strlen(map[line_p]);
        }
        else if (valid_char(map, line_p, char_p, id) == -1)
            return (-1);
    }
    return (1);
}

/*Checking that space inside the map are surrounded by walls*/
int inside_space_bounded(char **map)
{
    return (0);
}

/*Function handling check for outerbound*/
int valid_map(char **map, int height)
{
    int pos;

    pos = 0;
    if (valid_outer_line(map, pos, FIRST_LINE) == -1)
        return (free_map(map), -1);
    pos = height - 1;
    if (valid_outer_line(map, pos, LAST_LINE) == -1)
        return (free_map(map), -1);
    if (valid_col(map, FIRST_COL) == -1)
        return (free_map(map), -1);
    if (valid_col(map, LAST_COL) == -1)
        return (free_map(map), -1);
    dprintf(STDERR_FILENO, "map is valid for now !\n");
    return (1);
}