/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:15:42 by almeddah          #+#    #+#             */
/*   Updated: 2025/03/25 13:53:29 by almeddah         ###   ########.fr       */
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

void	moove_down(t_data *data)
{
	if (data->map[data->player.y + 1][data->player.x].content == 'T')
	{
		ft_printf("Game over\nYou died from a trap\n");
		data->quit = 1;
		return ;
	}
	else if (data->map[data->player.y + 1][data->player.x].content == 'E')
		moove_exit(data);
	else if (data->map[data->player.y + 1][data->player.x].content != '1')
	{
		if (data->map[data->player.y + 1][data->player.x].content == 'C')
		{
			data->chests--;
			if (data->chests == 0)
				data->img_exit = data->img_door_open;
		}
		data->map[data->player.y][data->player.x].content = '0';
		data->player.y++;
		data->moves++;
		data->map[data->player.y][data->player.x].content = 'P';
	}
	data->img_player = data->img_player_face;
	draw_grid(data);
}

void	moove_up(t_data *data)
{
	if (data->map[data->player.y - 1][data->player.x].content == 'T')
	{
		ft_printf("Game over\nYou died from a trap\n");
		data->quit = 1;
		return ;
	}
	else if (data->map[data->player.y - 1][data->player.x].content == 'E')
		moove_exit(data);
	else if (data->map[data->player.y - 1][data->player.x].content != '1')
	{
		if (data->map[data->player.y - 1][data->player.x].content == 'C')
		{
			data->chests--;
			if (data->chests == 0)
				data->img_exit = data->img_door_open;
		}
		data->map[data->player.y][data->player.x].content = '0';
		data->player.y--;
		data->moves++;
		data->map[data->player.y][data->player.x].content = 'P';
	}
	data->img_player = data->img_player_back;
	draw_grid(data);
}

void	moove_left(t_data *data)
{
	if (data->map[data->player.y][data->player.x - 1].content == 'T')
	{
		ft_printf("Game over\nYou died from a trap\n");
		data->quit = 1;
		return ;
	}
	else if (data->map[data->player.y][data->player.x - 1].content == 'E')
		moove_exit(data);
	else if (data->map[data->player.y][data->player.x - 1].content != '1')
	{
		if (data->map[data->player.y][data->player.x - 1].content == 'C')
		{
			data->chests--;
			if (data->chests == 0)
				data->img_exit = data->img_door_open;
		}
		data->map[data->player.y][data->player.x].content = '0';
		data->player.x--;
		data->moves++;
		data->map[data->player.y][data->player.x].content = 'P';
	}
	data->img_player = data->img_player_left;
	draw_grid(data);
}

void	moove_right(t_data *data)
{
	if (data->map[data->player.y][data->player.x + 1].content == 'T')
	{
		ft_printf("Game over\nYou died from a trap\n");
		data->quit = 1;
		return ;
	}
	else if (data->map[data->player.y][data->player.x + 1].content == 'E')
		moove_exit(data);
	else if (data->map[data->player.y][data->player.x + 1].content != '1')
	{
		if (data->map[data->player.y][data->player.x + 1].content == 'C')
		{
			data->chests--;
			if (data->chests == 0)
				data->img_exit = data->img_door_open;
		}
		data->map[data->player.y][data->player.x].content = '0';
		data->player.x++;
		data->moves++;
		data->map[data->player.y][data->player.x].content = 'P';
	}
	data->img_player = data->img_player_right;
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
