/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:16:25 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/18 14:18:01 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Get the heigh of the map to alloc the char ** 
& check that the map description contains ONLY authorized characters*/
int get_height(int fd_config, char *config_file)
{
    int     height;
    int     ret_map;
    char    *line;

    height = 0;
    close(fd_config);
    fd_config = open(config_file, O_RDONLY);
    while (1)
    {
        ret_map = 0;
        line = get_next_line(fd_config);
        if (!line)
            break; 
        ret_map = is_map(line);
        if (ret_map == 1)
            height++;
        else if (ret_map == -1 
                || (height > 0 && !ret_map))
            return (-1);
        free(line);
    }
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
        if (is_map(line) == 1) //externaliser
        {
            map[i] = my_strdup(line);
            i++;
        }
        free(line);
    }
    map[i] = NULL;
    return (map);
}

int valid_char(char **map, int line_p, int char_p, int top)
{
    dprintf(STDERR_FILENO, "line %d, char %d: '%c'\n", line_p, char_p, map[line_p][char_p]);
    if (map[line_p][char_p] == '1')
        return (1);
    else if (is_space(map[line_p][char_p]))
    {
        if (top)
            line_p++;
        else
            line_p--;
        return (valid_char(map, line_p, char_p, top));
    }
    else // == '0' or N S W E
        return (error_msg_map(2));
}

int valid_outer_line(char **map, int line_p, int top)
{
    int char_p;

    char_p = 0;
    while(map[line_p][char_p])
    {
        if (valid_char(map, line_p, char_p, top) == 1)
            char_p++;
        else if (valid_char(map, line_p, char_p, top) == -1)
            return (-1);
    }
    return (1);
}

int valid_map(char **map, int height)
{
    int line_pos;

    line_pos = 0;
    if (valid_outer_line(map, line_pos, 1) == -1)
    {
        dprintf(STDERR_FILENO, "invalid first line !\n");
        free_map(map); //to move at the end of the code once I merge with the rest
        return (-1);
    }
    line_pos = height - 1;
    if (valid_outer_line(map, line_pos, 0) == -1)
    {
        dprintf(STDERR_FILENO, "invalid last line !\n");
        free_map(map); //to move at the end of the code once I merge with the rest
        return (-1);
    }
    dprintf(STDERR_FILENO, "map is valid for now !\n");
    return (1);
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
    height = get_height(fd_config, config_file);
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
