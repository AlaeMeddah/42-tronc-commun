/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:21:44 by almeddah          #+#    #+#             */
/*   Updated: 2025/03/25 13:49:20 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	moove_exit(t_data *data)
{
	if (data->chests == 0)
	{
		data->moves++;
		ft_printf("Game cleared\nYou cleared it in %d moves\n", data->moves);
		data->quit = 1;
	}
}

void	put_image_to_window(t_data *data, int x, int y, void *img)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, data->map[y][x].x
		* data->img_width, data->map[y][x].y * data->img_height);
}

void	ft_string_put(t_data *data)
{
	char	*str;
	char	*moves;

	moves = ft_itoa(data->moves);
	str = ft_strjoin("moves : ", moves);
	ft_printf("%s\n", str);
	free(str);
	free(moves);
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
			else if (data->map[y][x].content == 'T')
				put_image_to_window(data, x, y, data->img_trap);
		}
	}
}

int	handle_expose(t_data *data)
{
	draw_grid(data);
	return (0);
}
