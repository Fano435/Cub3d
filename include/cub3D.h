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

# include "../libft/libft.h"
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
	int			width;
	int			height;
}				t_img;

// typedef struct s_texture
// {
// 	void		*ptr;
// 	char		*addr;
// 	char		*path;
// 	int			bits_per_pixel;
// 	int			line_len;
// 	int			endian;
// 	int			width;
// 	int			height;
// }				t_texture;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		angle;
	int			fov;

	bool		key_up;
	bool		key_right;
	bool		key_down;
	bool		key_left;
	bool		rotate_l;
	bool		rotate_r;
}				t_player;

typedef struct s_ray
{
	double		angle;
	int			map_x;
	int			map_y;
	double		hit_x[2];
	double		hit_y[2];
	double		wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			side;
}				t_ray;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img *img; // a virer une fois toutes les textures parse ??
	// t_texture	*north_text;
	// t_texture	*south_text;
	// t_texture	*east_text;
	// t_texture	*west_text;
	t_img		textures[4];
	int			floor_color;
	int			ceiling_color;
	t_player	*player;
	t_ray		*ray;
}				t_game;

// render.c
void			render_wall(t_game *game, t_ray *ray, int pos);
void			render_floor_ceiling(t_game *game, t_ray *ray, int pos);
bool			touch(int x, int y);
void			pixel_put(t_img *img, int x, int y, int color);

// debug.c
void			draw_map(char map[10][8], t_img *img);
void			draw_square(int x, int y, int size, t_img *img);

// events.c
int				close_game(t_game *game);
int				key_press(int keysym, t_player *player);
int				key_release(int keysym, t_game *game);

// init.c
void			init(t_game *game);
void			init_player(t_player *player);
void			init_ray(t_ray *ray);

// player.c
void			rotate_player(t_player *player);

// raycasting.c
void			cast_rays(t_game *game);

// parsing.c
int				parsing(int argc, char **argv, t_game *game);
int				parse_texture(char *line, int *done, int id, t_game *game);
int				arg_parsing(int argc, char **argv);

// parsing_utils.c
int				is_texture(char *line, int *id);
int				error_msg(int error_code);
int				get_texture_file(char **texture_file, char *line, int pos);

// parsing_libft.c
int				is_space(char c);
int				is_digit(char c);
int				my_strncmp(const char *s1, const char *s2, int n);

// parsing_color.c
int				is_color(char *line, int *id);
int				get_color(char *line, int *pos, int first_nb);
int				parse_color(char *line, int *done, int id, t_game *game);

// parsing_map.c
int				parse_map(char *config_file, int done, int fd_config);
int				is_map(char *line);

# define WIN_WIDTH 960
# define WIN_HEIGHT 540
# define BLOCK 48
# define FOV 60

# define X 0
# define Y 1
# define W 119
# define A 97
# define S 115
# define D 100
# define KEY_ESC 65307
# define LEFT 65361
# define RIGHT 65363

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define C 6
# define F 7

// FOR DEBUG ONLY//
# define RED "\x1B[31m"
# define RESET "\x1B[0m"
/////////////////

#endif
