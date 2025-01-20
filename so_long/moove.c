/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:15:42 by almeddah          #+#    #+#             */
/*   Updated: 2025/01/20 18:36:13 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	moove_down(t_data *data)
{
	if (data->map[data->player.y + 1][data->player.x].content != '1')
	{
		if (data->map[data->player.y + 1][data->player.x].content == 'E')
		{
			if (data->chests == 0)
			{
				data->mooves++;
				ft_printf("Jeu terminé en %d déplacements\n", data->mooves);
				data->quit = 1;
			}
			return ;
		}
		if (data->map[data->player.y + 1][data->player.x].content == 'C')
			data->chests--;
		data->map[data->player.y][data->player.x].content = '0';
		data->player.y++;
		data->mooves++;
		ft_printf("Nombre de déplacements : %d\n", data->mooves);
		data->map[data->player.y][data->player.x].content = 'P';
	}
	draw_grid(data);
}

void	moove_up(t_data *data)
{
	if (data->map[data->player.y - 1][data->player.x].content != '1')
	{
		if (data->map[data->player.y - 1][data->player.x].content == 'E')
		{
			if (data->chests == 0)
			{
				data->mooves++;
				ft_printf("Jeu terminé en %d déplacements\n", data->mooves);
				data->quit = 1;
			}
			return ;
		}
		if (data->map[data->player.y - 1][data->player.x].content == 'C')
			data->chests--;
		data->map[data->player.y][data->player.x].content = '0';
		data->player.y--;
		data->mooves++;
		ft_printf("Nombre de déplacements : %d\n", data->mooves);
		data->map[data->player.y][data->player.x].content = 'P';
	}
	draw_grid(data);
}

void	moove_left(t_data *data)
{
	if (data->map[data->player.y][data->player.x - 1].content != '1')
	{
		if (data->map[data->player.y][data->player.x - 1].content == 'E')
		{
			if (data->chests == 0)
			{
				data->mooves++;
				ft_printf("Jeu terminé en %d déplacements\n", data->mooves);
				data->quit = 1;
			}
			return ;
		}
		if (data->map[data->player.y][data->player.x - 1].content == 'C')
			data->chests--;
		data->map[data->player.y][data->player.x].content = '0';
		data->player.x--;
		data->mooves++;
		ft_printf("Nombre de déplacements : %d\n", data->mooves);
		data->map[data->player.y][data->player.x].content = 'P';
	}
	draw_grid(data);
}

void	moove_right(t_data *data)
{
	if (data->map[data->player.y][data->player.x + 1].content != '1')
	{
		if (data->map[data->player.y][data->player.x + 1].content == 'E')
		{
			if (data->chests == 0)
			{
				data->mooves++;
				ft_printf("Jeu terminé en %d déplacements\n", data->mooves);
				data->quit = 1;
			}
			return ;
		}
		if (data->map[data->player.y][data->player.x + 1].content == 'C')
			data->chests--;
		data->map[data->player.y][data->player.x].content = '0';
		data->player.x++;
		data->mooves++;
		ft_printf("Nombre de déplacements : %d\n", data->mooves);
		data->map[data->player.y][data->player.x].content = 'P';
	}
	draw_grid(data);
}

int	key_handler(int keycode, t_data *data)
{
	if (keycode == 65307)
		data->quit = 1;
	else if (keycode == 119)
		moove_up(data);
	else if (keycode == 97)
		moove_left(data);
	else if (keycode == 115)
		moove_down(data);
	else if (keycode == 100)
		moove_right(data);
	return (0);
}
