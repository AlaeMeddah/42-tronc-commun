/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:18:39 by almeddah          #+#    #+#             */
/*   Updated: 2025/01/31 19:10:04 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	set_img(t_data *data)
{
	data->floor_file = "texture/floor.xpm";
	data->wall_file = "texture/wall.xpm";
	data->chest_file = "texture/chest.xpm";
	data->player_file = "texture/player.xpm";
	data->exit_file = "texture/exit.xpm";
	data->trap_file = "texture/trap.xpm";
	data->img_wall = mlx_xpm_file_to_image(data->mlx_ptr, data->wall_file,
			&(data->img_width), &(data->img_height));
	data->img_floor = mlx_xpm_file_to_image(data->mlx_ptr, data->floor_file,
			&(data->img_width), &(data->img_height));
	data->img_exit = mlx_xpm_file_to_image(data->mlx_ptr, data->exit_file,
			&(data->img_width), &(data->img_height));
	data->img_chest = mlx_xpm_file_to_image(data->mlx_ptr, data->chest_file,
			&(data->img_width), &(data->img_height));
	data->img_player = mlx_xpm_file_to_image(data->mlx_ptr, data->player_file,
			&(data->img_width), &(data->img_height));
	data->img_trap = mlx_xpm_file_to_image(data->mlx_ptr, data->trap_file,
			&(data->img_width), &(data->img_height));
	if (!data->img_wall || !data->img_floor || !data->img_chest
		|| !data->img_exit || !data->img_player || !data->img_trap)
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
