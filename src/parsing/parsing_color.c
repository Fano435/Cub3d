/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:55:13 by aubertra          #+#    #+#             */
/*   Updated: 2025/03/07 14:56:28 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*Return the id corresponding to the color (floor or ceilling))*/
int	is_color(char *line, int *id)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	*id = 0;
	if (!my_strncmp(&line[i], "F", ft_strlen("F")))
		*id = F;
	else if (!my_strncmp(&line[i], "C", ft_strlen("C")))
		*id = C;
	return (*id);
}

/*get each R G B in int format*/
int	get_color(char *line, int *pos, int first_nb)
{
	long long	color;
	int			count;
	int			not_zero;

	if (first_nb)
		while (line[*pos] && (is_space(line[*pos])))
			(*pos)++;
	else
		while (line[*pos] && (is_space(line[*pos]) || line[*pos] == ','))
			(*pos)++;
	color = 0;
	count = 0;
	not_zero = 0;
	while (line[*pos] && is_digit(line[*pos]))
	{
		color = color * 10 + (line[*pos] - '0');
		(*pos)++;
		if (line[*pos] != '0')
			not_zero = 1;
		if (not_zero)
			count++;
	}
	if (color < 0 || color > 255 || count > 10)
		return (-1);
	return ((int)color);
}

/*Adding the converted color to the proper variable of the game struct
depending on if it is referring to floor or to ceiling*/
int	add_color_game(int id, t_game *game, int converted_color)
{
	if (id == C)
	{
		if (game->ceiling_color != -1)
			return (error_msg(4));
		game->ceiling_color = converted_color;
		return (0);
	}
	else if (id == F)
	{
		if (game->floor_color != -1)
			return (error_msg(4));
		game->floor_color = converted_color;
		return (0);
	}
	return (-1);
}

/*Main function for parsing of the colors*/
int	parse_color(char *line, int *done_col, int id, t_game *game)
{
	int	red;
	int	green;
	int	blue;
	int	pos;
	int	converted_color;

	if (*done_col >= 2)
		return (error_msg(4));
	pos = 2;
	red = get_color(line, &pos, 1);
	green = get_color(line, &pos, 0);
	blue = get_color(line, &pos, 0);
	if (red < 0 || blue < 0 || green < 0)
		return (error_msg(7));
	while (line[pos])
	{
		if (!is_space(line[pos]))
			return (error_msg(7));
		pos++;
	}
	converted_color = (red << 16 | green << 8 | blue);
	if (add_color_game(id, game, converted_color))
		return (-1);
	(*done_col)++;
	return (0);
}
