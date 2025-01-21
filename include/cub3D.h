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
# include <stdbool.h>
# include <stdio.h>
# include <string.h>

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_player
{
	float		x;
	float		y;
	double		angle;

	bool		key_up;
	bool		key_right;
	bool		key_down;
	bool		key_left;
	bool		rotate_l;
	bool		rotate_r;
}				t_player;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		*img;
	t_player	*player;
}				t_game;

// events.c
int				close_game(t_game *game);
int				key_press(int keysym, t_player *player);
int				key_release(int keysym, t_game *game);

// player.c
void			init_player(t_player *player);
void			move_player(t_player *player);

# define WIN_WIDTH 960
# define WIN_HEIGHT 540
# define BLOCK 32

# define W 119
# define A 97
# define S 115
# define D 100
# define KEY_ESC 65307
# define LEFT 65361
# define RIGHT 65363
# define PI 3.14159

#endif
