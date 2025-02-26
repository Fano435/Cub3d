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
	char		*path;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

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
	double		vertical_hit;
	double		horizontal_hit;
	double		wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			side;
}				t_ray;

typedef struct s_game
{
	char		**map;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		*img;
	t_img		*img_text_n;
	t_img		*img_text_s;
	t_img		*img_text_e;
	t_img		*img_text_w;
	int			floor_color;
	int			ceiling_color;
	int			map_height;
	int			map_width;
	t_player	*player;
	t_ray		*ray;
}				t_game;

// texture.c
int				get_pixel_color(t_game *game, t_ray *ray, int y);

// render.c
void			render_wall(t_game *game, t_ray *ray, int pos);
void			render_floor_ceiling(t_game *game, t_ray *ray, int pos);
void			pixel_put(t_img *img, int x, int y, int color);

// debug.c
void			draw_map(char **map, t_img *img);
void			draw_square(int x, int y, int size, t_img *img);

// events.c
int				close_game(t_game *game);
int				key_press(int keysym, t_player *player);
int				key_release(int keysym, t_game *game);

// init.c
void			init(t_game *game);
void			init_player(t_player *player);
void			init_ray(t_ray *ray);
void			init_mlx_textures(t_game *game);

// player.c
void			move_player(t_game *game, t_player *player);
bool			touch(int x, int y, t_game *game);

// raycasting.c
void			cast_rays(t_game *game);

// raycasting_utils.c
void			get_wall_distance(t_game *game, t_ray *ray);

////////////////////////*PARSING*////////////////////////////////////////////

// parsing.c
int				error_msg(int error_code);
int				parsing(int argc, char **argv, t_game *game);
int				arg_parsing(int argc, char **argv);
int				parsing_text_col(int fd_config, int *done_text,
					int *done_col, t_game *game);

// parsing_libft.c
int				is_space(char c);
int				is_digit(char c);
int				my_strncmp(const char *s1, const char *s2, int n);
int				my_strcmp(const char *s1, const char *s2);

// parsing_color.c
int				is_color(char *line, int *id);
int				get_color(char *line, int *pos, int first_nb);
int				parse_color(char *line, int *done, int id, t_game *game);

// parsing_map.c
int				parse_map(char *config_file, int fd_config, t_game *game);
int				get_height(int fd_config, t_game *game);
char			**file_to_array(int fd_config, char *config_file, t_game *game);
int				is_map(char *line, int *player_pos, t_game *game);
int				get_starting_pos(char **map, t_game *game);

// parsing_texture.c
int				is_texture(char *line, int *id);
int				get_texture_file(char **texture_file, char *line, int pos);
int				parse_texture(char *line, int *done, int id, t_game *game);
int				add_text_to_game(char *texture_file, int id, t_game *game);

// parsing_map_bound.c
int				valid_map(t_game *game);
void			flood_fill(char **map, int x, int y, int height);
int				check_flooded_map(char **map, int height);

// parsing_map_utils.c
int				error_msg_map(int error_code);
void			print_map(char **map);
void			free_map(char **map);
char			**copy_map(char **original, int height);
int				add_pos_game(int x, int y, int found, t_game *game);

# define WIN_WIDTH 960
# define WIN_HEIGHT 540
# define BLOCK 32
# define FOV 60

// # define X 0
// # define Y 1
# define W 119
# define A 97
# define S 115
# define D 100
# define KEY_ESC 65307
# define LEFT 65361
# define RIGHT 65363

# define NO 2
# define SO 3
# define WE 4
# define EA 5
# define C 6
# define F 7

# define M_PI 3.14159265358979323846

// FOR DEBUG ONLY//
# define RED "\x1B[31m"
# define RESET "\x1B[0m"
/////////////////

#endif
