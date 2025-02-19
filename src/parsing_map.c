/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:16:25 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/19 10:23:22 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Get the heigh of the map to alloc the char ** 
& check that the map description contains ONLY authorized characters*/
int get_height(int fd_config)
{
    int     height;
    int     ret_map;
    char    *line;
    int     player_pos;
    int     stop;

    height = 0;
    player_pos = 0;
    stop = 0;
    while (1)
    {
        line = get_next_line(fd_config);
        if (!line)
            break;
        if (!stop)
            ret_map = is_map(line, &player_pos);
        if (ret_map == 1)
            height++;
        else if (ret_map == -1 || (height > 0 && !ret_map))
            stop = 1;
        free(line);
    }
    if (stop)
        return (-1);
    return (height);
}

/*Convert the map into a char ** to finish the parsing*/
char **file_to_array(int fd_config, char *config_file, int height)
{
    char    **map;
    char    *line;
    int     i;

    close(fd_config);
    fd_config = open(config_file, O_RDONLY);
    map = (char **)malloc(sizeof(char *) * (height + 1));
    if (!map)
        return (error_msg(6), NULL);
    i = 0;
    while (1)
    {
        line = get_next_line(fd_config);
        if (!line)
            break;
        if (is_map(line, NULL) == 1) //externaliser
        {
            map[i] = my_strdup(line);
            i++;
        }
        free(line);
    }
    map[i] = NULL;
    return (map);
}

/*Main fonction handling the parsing of the map*/
int parse_map(char *config_file, int done, int fd_config)
{
    char    **map;
    int     height;

    if (done != 6)
        return (error_msg(4));
    close(fd_config);
    fd_config = open(config_file, O_RDONLY);
    height = get_height(fd_config);
    if (height < 1)
        return (-1);
    map = file_to_array(fd_config, config_file, height);
    if (!map)
        return (-1); //chekc proper error msg
    print_map(map); //only for debug
    if (valid_map(map, height) == -1)
        return (-1); //make sure to add proper error_msg
    done++;
    free_map(map); //to move at the end of the code once I merge with the rest
    return (0);
}
