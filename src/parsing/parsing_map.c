/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:16:25 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/11 14:46:02 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int error_msg_map(int error_code)
{
    char    *msg;

    write(STDERR_FILENO, "Error\n", 6);
    if (error_code == 1)
        msg = "Map should only contains 0 (floor), 1 (walls) and\n";
    write(STDERR_FILENO, msg, ft_strlen(msg));
    return (-1);
}

int is_map(char *line)
{
    int pos;

    pos = 0;
    while (line[pos])
    {
        if (line[pos] != '1' && line[pos] != '0' 
            && !is_space(line[pos]) && line[pos] != 'N'
            && line[pos] != 'S' && line[pos] != 'E'
            && line[pos] != 'W')
            return (error_msg_map(1));
        pos++;
    }
    return (1);
}

int parse_map(char *config_file, int done, int fd_config)
{
    // char    **map;
    char    *line;
    int     height;
    int     ret_map;
    
    if (done != 6)
        return (error_msg(4));
    close(fd_config);
    fd_config = open(config_file, O_RDONLY);
    height = 0;
    while (1)
    {
        ret_map = 0;
        line = get_next_line(fd_config);
        if (!line)
            break; 
        dprintf(STDERR_FILENO, "line is: %s", line);
        ret_map = is_map(line);
        dprintf(STDERR_FILENO, "ret is %d\n", ret_map);
        free(line);
        if (ret_map == 1)
            height++;
        else if (ret_map == -1)
            return (-1);
    }
    dprintf(STDERR_FILENO, "height is %d\n", height);
    done++;
    return (0);
}
