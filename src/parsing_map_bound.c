/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_bound.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:49:07 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/18 17:21:17 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void    flood_fill(char **map, int x, int y, int height)
{
    if (x < 0 || y < 0 || x > ((int)ft_strlen(map[y]) - 1) 
        || y > (height - 1) || map[y][x] == '1' || map[y][x] == 'F')
        return ;
    map[y][x] = 'F';
    flood_fill(map, x - 1, y, height);
    flood_fill(map, x + 1, y, height);
    flood_fill(map, x, y - 1, height);
    flood_fill(map, x, y + 1, height);
}

int valid_map(char **map, int height)
{
    int     x;
    int     y;
    int     found;

    x = 0;
    y = 0;
    found = 0;
    while (map[y]) //sera externaliser dans une fonciton une fois la struct rempli
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == 'N' || map[y][x] == 'W'
                || map[y][x] == 'E' || map[y][x] == 'S')
            {
                found = 1;
                break;
            }
            x++;
        }
        if (found == 1)
            break;
        y++;
    }///////////////////////////fonction se finira ici
    dprintf(STDERR_FILENO, "player starts in pos x: %d, y is %d\n", x, y);
    flood_fill(map, x, y, height); //maybe do it with a copied map to avoid any issues 
    // if (check_flooded_map)
    print_map(map);
    dprintf(STDERR_FILENO, RED "Map is valid !\n" RESET);
    return (1);
}
