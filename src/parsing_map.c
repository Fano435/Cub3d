/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:16:25 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/18 11:33:26 by aubertra         ###   ########.fr       */
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
        pos++;
    }
    return (1);
}
int get_len(char *line, int max_len)
{
    int     pos;

    pos = 0;
    while (line[pos])
        pos++;
    if (pos > max_len)
        return (pos);
    else
        return (max_len);
}

int get_height(int fd_config, char *config_file)
{
    int     height;
    int     ret_map;
    char    *line;
    int     max_len;

    height = 0;
    max_len = 0;
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
        else if (ret_map == -1)
            return (-1);
        max_len = get_len(line, max_len);
        free(line);
    }
    return (height);
}

int get_len2(int fd_config, char *config_file)
{
    int     height;
    int     ret_map;
    char    *line;
    int     max_len;

    height = 0;
    max_len = 0;
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
        else if (ret_map == -1)
            return (-1);
        max_len = get_len(line, max_len);
        free(line);
    }
    return (max_len);
}

char **file_to_array(int fd_config, char *config_file, int len, int height)
{
    char    **map;
    char    *line;
    int     i;
    int     j;
    int     pos;

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
        if (is_map(line) == 1)
        {
            pos = 0;
            map[i] = (char *)malloc(sizeof(char) * (len + 1));
            if (!map[i])
                return (error_msg(6), NULL);
            j = 0;
            while (line[pos])
            {
                map[i][j] = line[pos];
                j++;
                pos++;
            }
            map[i][j] = '\0';
        }
    }
    map[i] = NULL;
    return (map);
}

int parse_map(char *config_file, int done, int fd_config)
{
    char    **map;
    int     height;
    int     len;

    if (done != 6)
        return (error_msg(4));
    close(fd_config);
    fd_config = open(config_file, O_RDONLY);
    height = get_height(fd_config, config_file);
    len = get_len2(fd_config, config_file);
    dprintf(STDERR_FILENO, "len is %d\n", len);
    dprintf(STDERR_FILENO, "height is %d\n", height);
    if (height < 1 || len < 1)
        return (-1);
    map = file_to_array(fd_config, config_file, len, height);
    // print_map();
    done++;
    return (0);
}
