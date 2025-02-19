/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:16:25 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/19 10:21:41 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Personnalized error message concerning the map*/
int error_msg_map(int error_code)
{
    char    *msg;

    write(STDERR_FILENO, "Error\n", 6);
    if (error_code == 1)
        msg = "Map description should only contains 0 (floor), 1 (walls) and 1 player orientation indicator (N, S, E, W)\n";
    if (error_code == 2)
        msg = "Map is not bound by walls\n";
    if (error_code == 3)
        msg = "Map description cannot contain more than 1 starting position for the player\n";
    write(STDERR_FILENO, msg, ft_strlen(msg));
    return (-1);
}

/*Check if the line is part of the map/contain only authorize map characters*/
int is_map(char *line, int *player_pos)
{
    int pos;
    int id;

    pos = 0;
    if (is_color(line, &id) || is_texture(line, &id) || line[pos] == '\n')
        return (0);
    while (line[pos])
    {
        if (line[pos] != '1' && line[pos] != '0' 
            && !is_space(line[pos]) && line[pos] != 'N'
            && line[pos] != 'S' && line[pos] != 'E'
            && line[pos] != 'W')
            return (error_msg_map(1));
        if (player_pos && (line[pos] == 'N' || line[pos] == 'S' 
            || line[pos] == 'E' || line[pos] == 'W'))
            (*player_pos)++;
        if (player_pos && *player_pos > 1)
            return (error_msg_map(3));
        pos++;
    }
    return (1);
}

/*Display the map (DEBUG ONLY)*/
void    print_map(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            dprintf(STDERR_FILENO, "%c", map[i][j]);
            j++;
        }
        dprintf(STDERR_FILENO, "\n");
        i++;
    }
}

/*Free the map at the end of the code*/
void    free_map(char **map)
{
    int i;

    i = 0;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}
