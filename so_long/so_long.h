/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:24:21 by alae              #+#    #+#             */
/*   Updated: 2025/01/16 20:09:10 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"

typedef struct s_map
{
	char	content;
	int		visited;
	int		x;
	int		y;
}			t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
	int		img_width;
	int		img_height;
	t_map	**map;
	t_map	player;
	t_map	exit;
	int		chests;
	char	*floor_file;
	char	*wall_file;
	char	*player_file;
	char	*chest_file;
	char	*exit_file;
	void	*img_floor;
	void	*img_wall;
	void	*img_player;
	void	*img_chest;
	void	*img_exit;
	int		quit;
}			t_data;
int			map(char *map_file, t_data *data);
void		free_map(t_map **map, int y);

#endif
