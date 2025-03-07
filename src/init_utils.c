/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:06:14 by aubertra          #+#    #+#             */
/*   Updated: 2025/03/07 14:42:16 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*Displaying the correct error message for mlx initialisation issue*/
int	error_msg_mlx(int error_code)
{
	char	*msg;

	write(STDERR_FILENO, "Error\n", 6);
	if (error_code == 0)
        msg = "mlx_xmp_file_to_image failed. Look at init.c\n";
    else if (error_code == 1)
        msg = "mlx_get_data_addr failed. Look at init.c\n";
    else if (error_code == 2)
        msg = "mlx_init of mlx_ptr failed. Look at init.c\n";
    else if (error_code == 3)
        msg = "mlx_new_window failed. Look at main.c\n";
    write(STDERR_FILENO, msg, ft_strlen(msg));
	return (-1);
}

int init_mlx_img(t_game *game)
{
    game->img_text_e->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr,
        game->img_text_e->path, &game->img_text_e->width,
        &game->img_text_e->height);
    if (!game->img_text_e->mlx_img)
        return(error_msg_mlx(0));
    game->img_text_n->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->img_text_n->path, &game->img_text_n->width,
			&game->img_text_n->height);
	if (!game->img_text_n->mlx_img)
		return(error_msg_mlx(0));
    game->img_text_s->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr,
                game->img_text_s->path, &game->img_text_s->width,
                &game->img_text_s->height);
    if (!game->img_text_s->mlx_img)
        return(error_msg_mlx(0));
    game->img_text_w->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->img_text_w->path, &game->img_text_w->width,
			&game->img_text_w->height);
	if (!game->img_text_w->mlx_img)
			return(error_msg_mlx(0));
    return (0);
}

int malloc_img(t_game *game)
{
    game->img = malloc(sizeof(t_img));
	if (!game->img)
		return (error_msg(6));
	game->img_text_e = malloc(sizeof(t_img));
	if (!game->img_text_e)
		return (error_msg(6));
    game->img_text_s = malloc(sizeof(t_img));
	if (!game->img_text_s)
		return (error_msg(6));
    game->img_text_n = malloc(sizeof(t_img));
	if (!game->img_text_n)
		return (error_msg(6));
    game->img_text_w = malloc(sizeof(t_img));
    if (!game->img_text_w)
        return (error_msg(6));
    return (0);
}


