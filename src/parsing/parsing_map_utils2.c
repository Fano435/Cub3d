/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:21:43 by aubertra          #+#    #+#             */
/*   Updated: 2025/03/10 10:42:33 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*create_map_line(char *line, t_game *game)
{
	int		i;
	char	*new_line;
	int		len;

	new_line = malloc(sizeof(char) * game->map_width);
	if (!new_line)
		return (NULL);
	i = 0;
	len = ft_strlen(line);
	while (i < (game->map_width - 1))
	{
		if (i < len && line[i] != '\n')
			new_line[i] = line[i];
		else
			new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}
