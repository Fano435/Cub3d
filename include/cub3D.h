/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:34:05 by jrasamim          #+#    #+#             */
/*   Updated: 2025/01/16 17:34:07 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../src/gnl/get_next_line.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <string.h>

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
}			t_game;

int			ft_atoi(const char *nptr);

// events.c
int			close_game(t_game *game);
int			handle_keys(int keysym, t_game *game);

// check_argument.c
void		check_argument(int argc, char *argv[], t_game *game);

# define WIN_WIDTH 960
# define WIN_HEIGHT 540
# define KEY_LEFT 97
# define KEY_UP 119
# define KEY_RIGHT 100
# define KEY_DOWN 115
# define KEY_ESC 65307

#endif
