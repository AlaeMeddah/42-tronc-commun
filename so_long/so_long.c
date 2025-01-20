/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:01 by almeddah          #+#    #+#             */
/*   Updated: 2025/01/20 18:10:58 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <unistd.h>

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

int	set_img(t_data *data)
{
	data->img_height = 80;
	data->img_width = 80;
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
		printf("Error : Unable to load images\n");
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
	data->mooves = 0;
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
		if (data->map[data->player.y + 1][data->player.x].content == 'E')
		{
			if (data->chests == 0)
			{
				data->mooves++;
				printf("Jeu terminé en %d déplacements\n", data->mooves);
				data->quit = 1;
			}
			return ;
		}
		if (data->map[data->player.y + 1][data->player.x].content == 'C')
			data->chests--;
		data->map[data->player.y][data->player.x].content = '0';
		data->player.y++;
		data->mooves++;
		printf("Nombre de déplacements : %d\n", data->mooves);
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
				printf("Jeu terminé en %d déplacements\n", data->mooves);
				data->quit = 1;
			}
			return ;
		}
		if (data->map[data->player.y - 1][data->player.x].content == 'C')
			data->chests--;
		data->map[data->player.y][data->player.x].content = '0';
		data->player.y--;
		data->mooves++;
		printf("Nombre de déplacements : %d\n", data->mooves);
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
				printf("Jeu terminé en %d déplacements\n", data->mooves);
				data->quit = 1;
			}
			return ;
		}
		if (data->map[data->player.y][data->player.x - 1].content == 'C')
			data->chests--;
		data->map[data->player.y][data->player.x].content = '0';
		data->player.x--;
		data->mooves++;
		printf("Nombre de déplacements : %d\n", data->mooves);
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
				printf("Jeu terminé en %d déplacements\n", data->mooves);
				data->quit = 1;
			}
			return ;
		}
		if (data->map[data->player.y][data->player.x + 1].content == 'C')
			data->chests--;
		data->map[data->player.y][data->player.x].content = '0';
		data->player.x++;
		data->mooves++;
		printf("Nombre de déplacements : %d\n", data->mooves);
		data->map[data->player.y][data->player.x].content = 'P';
	}
	draw_grid(data);
}

int	handle_close(t_data *data)
{
	data->quit = 1;
	return (0);
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

char	*ft_strrchr(const char *s, int c)
{
	char	*result;

	result = 0;
	while (*s)
	{
		if (*s == (char)c)
			result = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		result = (char *)s;
	return (result);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] && i < n - 1)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	check_extension(char *map_file)
{
	char	*extension;

	extension = ft_strrchr(map_file, '.');
	if (!extension || ft_strncmp(extension, ".ber", 4) != 0)
	{
		printf("Error : map file must have a '.ber' extension\n");
		return (0);
	}
	return (1);
}

int	main(int arcg, char **argv)
{
	t_data	data;

	if (arcg != 2)
		printf("Error : wrong number of arguments\n");
	if (arcg != 2 || !check_extension(argv[1]))
		return (0);
	set_data(&data);
	if (!map(argv[1], &data))
		return (0);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		printf("Error : mlx_init failed\n");
	if (data.mlx_ptr && set_img(&data))
	{
		data.win_ptr = mlx_new_window(data.mlx_ptr, data.width * data.img_width,
				data.height * data.img_height, "So_long");
		mlx_expose_hook(data.win_ptr, handle_expose, &data);
		mlx_key_hook(data.win_ptr, key_handler, &data);
		mlx_hook(data.win_ptr, 17, 0, handle_close, &data);
		mlx_loop_hook(data.mlx_ptr, loop_hook, &data);
		mlx_loop(data.mlx_ptr);
		cleanup(&data);
	}
	free_map(data.map, data.height);
	return (0);
}
