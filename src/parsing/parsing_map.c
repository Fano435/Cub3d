/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:16:25 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/10 18:47:38 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int is_map(char *line)
{
    int pb;
    int pos;

    pb = 0;
    pos = 0;
    while (line[pos])
    {
        if (!(line[pos] == '1' || line[pos] == '0' 
            || is_space(line[pos])))
            pb = -1;
        pos++;
    }
    return (0);
}

int parse_map(int *done, int fd_config)
{
    char    **map;
    char    *line;
    int     height;

    if (done != 6)
        return (error_msg(4));
    height = 0;
    while (1)
    {
        line = get_next_line(fd_config);
        if (!line)
            break; 
        dprintf(STDOUT_FILENO, "line is: %s", line);
        if (is_map(line))
            height++;
        free(line);
    }
    done++;
    return (0);
}