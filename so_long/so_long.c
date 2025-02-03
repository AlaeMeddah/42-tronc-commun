/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:01 by almeddah          #+#    #+#             */
/*   Updated: 2025/02/03 11:42:56 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_close(t_data *data)
{
	data->quit = 1;
	return (0);
}

void	cleanup(t_data *data)
{
	if (data->img_wall)
		mlx_destroy_image(data->mlx_ptr, data->img_wall);
	if (data->img_floor)
		mlx_destroy_image(data->mlx_ptr, data->img_floor);
	if (data->img_door_closed)
		mlx_destroy_image(data->mlx_ptr, data->img_door_closed);
	if (data->img_door_open)
		mlx_destroy_image(data->mlx_ptr, data->img_door_open);
	if (data->img_chest)
		mlx_destroy_image(data->mlx_ptr, data->img_chest);
	if (data->img_player_back)
		mlx_destroy_image(data->mlx_ptr, data->img_player_back);
	if (data->img_player_face)
		mlx_destroy_image(data->mlx_ptr, data->img_player_face);
	if (data->img_player_left)
		mlx_destroy_image(data->mlx_ptr, data->img_player_left);
	if (data->img_player_right)
		mlx_destroy_image(data->mlx_ptr, data->img_player_right);
	if (data->img_trap)
		mlx_destroy_image(data->mlx_ptr, data->img_trap);
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

int	check_extension(char *map_file)
{
	char	*extension;

	extension = ft_strrchr(map_file, '.');
	if (!extension || ft_strncmp(extension, ".ber", 4) != 0)
	{
		ft_printf("Error : map file must have a '.ber' extension\n");
		return (0);
	}
	return (1);
}

int	main(int arcg, char **argv)
{
	t_data	data;

	if (arcg != 2)
		ft_printf("Error : wrong number of arguments\n");
	if (arcg != 2 || !check_extension(argv[1]))
		return (0);
	set_data(&data);
	if (!map(argv[1], &data))
		return (0);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		ft_printf("Error : mlx_init failed\n");
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
