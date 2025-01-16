#include "so_long.h"
#include <unistd.h>

void	draw_grid(t_data *data)
{
	int i, j;
	for (i = 0; i < data->height; i++)
	{
		for (j = 0; j < data->width; j++)
		{
			if (data->map[i][j].content == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->img_wall, data->map[i][j].x * data->img_width,
					data->map[i][j].y * data->img_height);
			else if (data->map[i][j].content == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->img_floor, data->map[i][j].x * data->img_width,
					data->map[i][j].y * data->img_height);
			else if (data->map[i][j].content == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->img_player, data->map[i][j].x * data->img_width,
					data->map[i][j].y * data->img_height);
			else if (data->map[i][j].content == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->img_chest, data->map[i][j].x * data->img_width,
					data->map[i][j].y * data->img_height);
			else if (data->map[i][j].content == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->img_exit, data->map[i][j].x * data->img_width,
					data->map[i][j].y * data->img_height);
		}
	}
}

int	set_img(t_data *data)
{
	// data->img_height = 80;
	// data->img_width = 80;
	data->floor_file = "texture/floor.xpm";
	data->wall_file = "texture/wall.xpm";
	data->chest_file = "texture/chest.xpm";
	data->player_file = "texture/player.xpm";
	data->exit_file = "texture/exit.xpm";
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
	if (!data->img_wall || !data->img_floor || !data->img_chest
		|| !data->img_exit || !data->img_player)
	{
		write(2, "Error: Unable to load tile images\n", 34);
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
	data->quit = 0;
}

int	handle_expose(t_data *data)
{
	draw_grid(data);
	return (0);
}

void	moove_down(t_data *data)
{
	if (data->map[data->player.y + 1][data->player.x].content != '1')
	{
		if (data->map[data->player.y + 1][data->player.x].content == 'E'
			&& data->chests > 0)
			return ;
		if (data->map[data->player.y + 1][data->player.x].content == 'C')
			data->chests--;
		data->map[data->player.y][data->player.x].content = '0';
		data->player.y++;
		data->map[data->player.y][data->player.x].content = 'P';
	}
	draw_grid(data);
}

void	moove_up(t_data *data)
{
	if (data->map[data->player.y - 1][data->player.x].content != '1')
	{
		if (data->map[data->player.y - 1][data->player.x].content == 'E'
			&& data->chests > 0)
			return ;
		if (data->map[data->player.y - 1][data->player.x].content == 'C')
			data->chests--;
		data->map[data->player.y][data->player.x].content = '0';
		data->player.y--;
		data->map[data->player.y][data->player.x].content = 'P';
	}
	draw_grid(data);
}

void	moove_left(t_data *data)
{
	if (data->map[data->player.y][data->player.x - 1].content != '1')
	{
		if (data->map[data->player.y][data->player.x - 1].content == 'E'
			&& data->chests > 0)
			return ;
		if (data->map[data->player.y][data->player.x - 1].content == 'C')
			data->chests--;
		data->map[data->player.y][data->player.x].content = '0';
		data->player.x--;
		data->map[data->player.y][data->player.x].content = 'P';
	}
	draw_grid(data);
}

void	moove_right(t_data *data)
{
	if (data->map[data->player.y][data->player.x + 1].content != '1')
	{
		if (data->map[data->player.y][data->player.x + 1].content == 'E'
			&& data->chests > 0)
			return ;
		if (data->map[data->player.y][data->player.x + 1].content == 'C')
			data->chests--;
		data->map[data->player.y][data->player.x].content = '0';
		data->player.x++;
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

int	main(void)
{
	t_data	data;

	set_data(&data);
	if (!map("carte/carte.ber", &data))
		return (0);
	if (!data.map)
		return (0);
	data.mlx_ptr = mlx_init();
	if (!set_img(&data))
		return (0);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width * data.img_width,
			data.height * data.img_height, "So_long");
	mlx_expose_hook(data.win_ptr, handle_expose, &data);
	mlx_key_hook(data.win_ptr, key_handler, &data);
	mlx_loop_hook(data.mlx_ptr, loop_hook, &data);
	mlx_loop(data.mlx_ptr);
	cleanup(&data);
	free_map(data.map, data.height);
	return (0);
}
