/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:24:28 by alae              #+#    #+#             */
/*   Updated: 2025/01/16 20:23:39 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_map **map, int y)
{
	int	i;

	i = 0;
	while (i < y)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	map_size(char *map_file, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (0);
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
		if (!line)
		{
			close(fd);
			return (0);
		}
		if (ft_strlen(line) != data.width + 1)
		{
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

int	map_creation(char *map_file, t_data *data)
{
	int		x;
	int		y;
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	data->map = malloc(data->height * sizeof(t_map *));
	if (!data->map || fd < 0)
		return (0);
	y = 0;
	while (y < data->height)
	{
		x = 0;
		data->map[y] = malloc(data->width * sizeof(t_map));
		line = get_next_line(fd);
		if (!data->map[y] || !line)
		{
			free_map(data->map, y);
			close(fd);
			return (0);
		}
		while (x < data->width)
		{
			data->map[y][x].content = line[x];
			data->map[y][x].visited = 0;
			data->map[y][x].x = x;
			data->map[y][x].y = y;
			x++;
		}
		free(line);
		y++;
	}
	close(fd);
	return (1);
}

int	check_wall(t_data data)
{
	int	i;
	int	j;

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
				return (0);
			i++;
		}
		j++;
	}
	if (!data->player.content || !data->exit.content || data->chests == 0)
		return (0);
	return (1);
}

int	check_feasable(t_map *location, int *collectibles, int *exit, t_map **map)
{
	if (location->visited == 1 || location->content == '1')
		return (0);
	if (location->content == 'C')
		(*collectibles)--;
	if (location->content == 'E')
		*exit = 1;
	location->visited = 1;
	if (*exit == 1 && *collectibles == 0)
		return (1);
	if (check_feasable(&map[location->y][location->x - 1], collectibles, exit,
			map))
		return (1);
	if (check_feasable(&map[location->y][location->x + 1], collectibles, exit,
			map))
		return (1);
	if (check_feasable(&map[location->y - 1][location->x], collectibles, exit,
			map))
		return (1);
	if (check_feasable(&map[location->y + 1][location->x], collectibles, exit,
			map))
		return (1);
	return (0);
}

void	print_map(t_map **map, int x, int y)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			printf("%c", map[i][j].content);
		}
		printf("\n");
	}
}

int	map(char *map_file, t_data *data)
{
	int	collectibles;
	int	exit;

	if (!map_size(map_file, data))
		return (0);
	if (!check_map_form(map_file, *data))
		return (0);
	if (!map_creation(map_file, data))
		return (0);
	if (!check_wall(*data))
		return (0);
	if (!check_componants(data))
		return (0);
	exit = 0;
	collectibles = data->chests;
	if (!check_feasable(&(data->player), &collectibles, &exit, data->map))
		return (0);
	return (1);
}
