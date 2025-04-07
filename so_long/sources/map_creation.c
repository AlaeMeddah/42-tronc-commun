/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:24:28 by alae              #+#    #+#             */
/*   Updated: 2025/04/07 15:16:39 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	free_map(t_map **map, int y)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (i < y)
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
	return (0);
}

int	map_size(char *map_file, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error : could not read the map file\n");
		return (0);
	}
	data->width = 0;
	data->height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		data->width = ft_strlen(line);
		data->height++;
		free(line);
	}
	close(fd);
	return (1);
}

int	fill_map_data(t_data *data, int fd)
{
	int		x;
	int		y;
	char	*line;

	y = -1;
	while (++y < data->height)
	{
		x = -1;
		data->map[y] = malloc(data->width * sizeof(t_map));
		line = get_next_line(fd);
		if (!data->map[y] || !line)
			return (y);
		while (++x < data->width)
		{
			data->map[y][x].content = line[x];
			data->map[y][x].visited = 0;
			data->map[y][x].x = x;
			data->map[y][x].y = y;
		}
		free(line);
	}
	line = get_next_line(fd);
	return (0);
}

int	map_creation(char *map_file, t_data *data)
{
	int	fd;
	int	result;

	fd = open(map_file, O_RDONLY);
	data->map = malloc(data->height * sizeof(t_map *));
	if (!data->map || fd < 0)
		return (0);
	result = fill_map_data(data, fd);
	close(fd);
	if (result != 0)
		return (0);
	return (1);
}

int	map(char *map_file, t_data *data)
{
	int	chests;
	int	exit;

	if (!map_size(map_file, data))
		return (0);
	if (!check_map_form(map_file, *data))
		return (0);
	if (!map_creation(map_file, data))
		return (free_map(data->map, data->height));
	if (!check_wall(*data))
	{
		ft_printf("Error : map must be closed\n");
		return (free_map(data->map, data->height));
	}
	if (!check_componants(data))
		return (free_map(data->map, data->height));
	exit = 0;
	chests = data->chests;
	if (!check_feasable(&(data->player), &chests, &exit, data->map))
	{
		ft_printf("Error : map must contain a valid path\n");
		return (free_map(data->map, data->height));
	}
	return (1);
}
