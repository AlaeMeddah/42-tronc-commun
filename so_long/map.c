/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:24:28 by alae              #+#    #+#             */
/*   Updated: 2025/01/20 17:53:56 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_map **map, int y)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < y)
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

int	map_size(char *map_file, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error : could not read the map file\n");
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

int	check_map_form(char *map_file, t_data data)
{
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (data.height > 1)
	{
		line = get_next_line(fd);
		if (!line || ft_strlen(line) != data.width + 1)
		{
			printf("Error: map must be rectangular\n");
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		data.height--;
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
		{
			free_map(data->map, y);
			return (0);
		}
		while (++x < data->width)
		{
			data->map[y][x].content = line[x];
			data->map[y][x].visited = 0;
			data->map[y][x].x = x;
			data->map[y][x].y = y;
		}
		free(line);
	}
	return (1);
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
	return (result);
}

int	check_wall(t_data data)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	while (i < data.width)
	{
		if (data.map[0][i].content != '1' || data.map[data.height
			- 1][i].content != '1')
			return (0);
		i++;
	}
	while (j < data.height)
	{
		if (data.map[j][0].content != '1' || data.map[j][data.width
			- 1].content != '1')
			return (0);
		j++;
	}
	return (1);
}

int	componants_error(t_data data, int i, int j)
{
	if (j < data.height && i < data.width)
	{
		if (data.map[j][i].content == 'P')
			printf("Error : map must not contain more than one player\n");
		if (data.map[j][i].content == 'E')
			printf("Error : map must not contain more than one exit\n");
		return (0);
	}
	if (!data.player.content)
		printf("Error :  map must contain a player\n");
	if (!data.exit.content)
		printf("Error :  map must contain an exit\n");
	if (!data.chests)
		printf("Error :  map must contain at least a collectible\n");
	return (0);
}

int	check_componants(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < data->height)
	{
		i = 0;
		while (i < data->width)
		{
			if (data->map[j][i].content == 'P' && !data->player.content)
				data->player = data->map[j][i];
			else if (data->map[j][i].content == 'E' && !data->exit.content)
				data->exit = data->map[j][i];
			else if (data->map[j][i].content == 'C')
				data->chests++;
			else if (data->map[j][i].content != '0'
				&& data->map[j][i].content != '1')
				return (componants_error(*data, i, j));
			i++;
		}
		j++;
	}
	if (!data->player.content || !data->exit.content || data->chests == 0)
		return (componants_error(*data, i, j));
	return (1);
}

int	check_feasable(t_map *location, int *chests, int *exit, t_map **map)
{
	if (location->visited == 1 || location->content == '1')
		return (0);
	if (location->content == 'C')
		(*chests)--;
	if (location->content == 'E')
		*exit = 1;
	location->visited = 1;
	if (*exit == 1 && *chests == 0)
		return (1);
	if (check_feasable(&map[location->y][location->x - 1], chests, exit, map))
		return (1);
	if (check_feasable(&map[location->y][location->x + 1], chests, exit, map))
		return (1);
	if (check_feasable(&map[location->y - 1][location->x], chests, exit, map))
		return (1);
	if (check_feasable(&map[location->y + 1][location->x], chests, exit, map))
		return (1);
	return (0);
}

// void	print_map(t_map **map, int x, int y)
// {
// 	for (int i = 0; i < y; i++)
// 	{
// 		for (int j = 0; j < x; j++)
// 		{
// 			printf("%c", map[i][j].content);
// 		}
// 		printf("\n");
// 	}
// }

int	map(char *map_file, t_data *data)
{
	int	chests;
	int	exit;

	if (!map_size(map_file, data))
		return (0);
	if (!check_map_form(map_file, *data))
		return (0);
	if (!map_creation(map_file, data))
		return (0);
	if (!check_wall(*data))
	{
		printf("Error : map must be closed\n");
		return (0);
	}
	if (!check_componants(data))
		return (0);
	exit = 0;
	chests = data->chests;
	if (!check_feasable(&(data->player), &chests, &exit, data->map))
	{
		printf("Error : map must contain a valid path\n");
		return (0);
	}
	return (1);
}
