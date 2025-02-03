/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:18:39 by almeddah          #+#    #+#             */
/*   Updated: 2025/02/03 11:31:38 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_mlx_img(t_data *data)
{
	data->img_wall = mlx_xpm_file_to_image(data->mlx_ptr, data->wall_file,
			&(data->img_width), &(data->img_height));
	data->img_floor = mlx_xpm_file_to_image(data->mlx_ptr, data->floor_file,
			&(data->img_width), &(data->img_height));
	data->img_door_closed = mlx_xpm_file_to_image(data->mlx_ptr,
			data->door_file_closed, &(data->img_width), &(data->img_height));
	data->img_door_open = mlx_xpm_file_to_image(data->mlx_ptr,
			data->door_file_open, &(data->img_width), &(data->img_height));
	data->img_chest = mlx_xpm_file_to_image(data->mlx_ptr, data->chest_file,
			&(data->img_width), &(data->img_height));
	data->img_player_back = mlx_xpm_file_to_image(data->mlx_ptr,
			data->player_file_back, &(data->img_width), &(data->img_height));
	data->img_player_face = mlx_xpm_file_to_image(data->mlx_ptr,
			data->player_file_face, &(data->img_width), &(data->img_height));
	data->img_player_left = mlx_xpm_file_to_image(data->mlx_ptr,
			data->player_file_left, &(data->img_width), &(data->img_height));
	data->img_player_right = mlx_xpm_file_to_image(data->mlx_ptr,
			data->player_file_right, &(data->img_width), &(data->img_height));
	data->img_trap = mlx_xpm_file_to_image(data->mlx_ptr, data->trap_file,
			&(data->img_width), &(data->img_height));
	data->img_player = data->img_player_face;
	data->img_exit = data->img_door_closed;
}

int	set_img(t_data *data)
{
	data->floor_file = "texture/floor.xpm";
	data->wall_file = "texture/wall.xpm";
	data->chest_file = "texture/gem.xpm";
	data->player_file_face = "texture/player_face.xpm";
	data->player_file_right = "texture/player_right.xpm";
	data->player_file_left = "texture/player_left.xpm";
	data->player_file_back = "texture/player_back.xpm";
	data->door_file_closed = "texture/door_closed.xpm";
	data->door_file_open = "texture/door_open.xpm";
	data->trap_file = "texture/trap.xpm";
	set_mlx_img(data);
	if (!data->img_wall || !data->img_floor || !data->img_chest
		|| !data->img_door_closed || !data->img_door_open
		|| !data->img_player_back || !data->img_player_face
		|| !data->img_player_left || !data->img_player_right || !data->img_trap)
	{
		ft_printf("Error : Unable to load images\n");
		return (0);
	}
	return (1);
}

void	set_data(t_data *data)
{
	data->map = NULL;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->player.content = '\0';
	data->exit.content = '\0';
	data->chests = 0;
	data->moves = 0;
	data->quit = 0;
}
