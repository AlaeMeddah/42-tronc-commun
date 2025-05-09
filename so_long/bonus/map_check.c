/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:26:28 by almeddah          #+#    #+#             */
/*   Updated: 2025/04/03 18:13:50 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_map_form(char *map_file, t_data data)
{
	int		fd;
	int		len;
	int		res;
	char	*line;

	res = 1;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		len = (int)ft_strlen(line);
		if (line[len - 1] == '\n')
			len = len - 1;
		if (len != data.width)
			res = 0;
		free(line);
	}
	if (res == 0)
		ft_printf("Error: map must be rectangular\n");
	close(fd);
	return (res);
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

int	componants_error(t_data data, int i, int j)
{
	if (j < data.height && i < data.width)
	{
		if (data.map[j][i].content == 'P')
			ft_printf("Error : map must not contain more than one player\n");
		if (data.map[j][i].content == 'E')
			ft_printf("Error : map must not contain more than one exit\n");
		else
			ft_printf("Error : invalid componants detected\n");
		return (0);
	}
	if (!data.player.content)
		ft_printf("Error :  map must contain a player\n");
	if (!data.exit.content)
		ft_printf("Error :  map must contain an exit\n");
	if (!data.chests)
		ft_printf("Error :  map must contain at least a collectible\n");
	return (0);
}

int	check_componants(t_data *data)
{
	int	i;
	int	j;

	j = -1;
	while (++j < data->height)
	{
		i = -1;
		while (++i < data->width)
		{
			if (data->map[j][i].content == 'P' && !data->player.content)
				data->player = data->map[j][i];
			else if (data->map[j][i].content == 'E' && !data->exit.content)
				data->exit = data->map[j][i];
			else if (data->map[j][i].content == 'C')
				data->chests++;
			else if (data->map[j][i].content != '0'
				&& data->map[j][i].content != '1'
				&& data->map[j][i].content != 'T')
				return (componants_error(*data, i, j));
		}
	}
	if (!data->player.content || !data->exit.content || data->chests == 0)
		return (componants_error(*data, i, j));
	return (1);
}

int	check_feasable(t_map *location, int *chests, int *exit, t_map **map)
{
	if (location->visited == 1 || location->content == '1'
		|| location->content == 'T')
		return (0);
	if (location->content == 'C')
		(*chests)--;
	if (location->content == 'E')
		*exit = 1;
	location->visited = 1;
	if (*exit == 1 && *chests == 0)
		return (1);
	if (location->content == 'E')
		return (0);
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
