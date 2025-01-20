/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:21:44 by almeddah          #+#    #+#             */
/*   Updated: 2025/01/20 18:24:35 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image_to_window(t_data *data, int x, int y, void *img)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, data->map[y][x].x
		* data->img_width, data->map[y][x].y * data->img_height);
}

void	draw_grid(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			if (data->map[y][x].content == '1')
				put_image_to_window(data, x, y, data->img_wall);
			else if (data->map[y][x].content == '0')
				put_image_to_window(data, x, y, data->img_floor);
			else if (data->map[y][x].content == 'P')
				put_image_to_window(data, x, y, data->img_player);
			else if (data->map[y][x].content == 'C')
				put_image_to_window(data, x, y, data->img_chest);
			else if (data->map[y][x].content == 'E')
				put_image_to_window(data, x, y, data->img_exit);
		}
	}
}

int	handle_expose(t_data *data)
{
	draw_grid(data);
	return (0);
}

void	cleanup(t_data *data)
{
	if (data->img_wall)
		mlx_destroy_image(data->mlx_ptr, data->img_wall);
	if (data->img_floor)
		mlx_destroy_image(data->mlx_ptr, data->img_floor);
	if (data->img_exit)
		mlx_destroy_image(data->mlx_ptr, data->img_exit);
	if (data->img_chest)
		mlx_destroy_image(data->mlx_ptr, data->img_chest);
	if (data->img_player)
		mlx_destroy_image(data->mlx_ptr, data->img_player);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

int	loop_hook(t_data *data)
{
	if (data->quit)
	{
		mlx_loop_end(data->mlx_ptr);
		return (0);
	}
	return (1);
}
