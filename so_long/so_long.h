/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:24:21 by alae              #+#    #+#             */
/*   Updated: 2025/04/07 15:14:26 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include "printf/ft_printf.h"

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
	char	*player_file_face;
	char	*player_file_back;
	char	*player_file_right;
	char	*player_file_left;
	char	*chest_file;
	char	*door_file_closed;
	char	*door_file_open;
	char	*trap_file;

	void	*img_floor;
	void	*img_wall;
	void	*img_player;
	void	*img_exit;
	void	*img_player_face;
	void	*img_player_back;
	void	*img_player_right;
	void	*img_player_left;
	void	*img_chest;
	void	*img_door_closed;
	void	*img_door_open;
	void	*img_trap;

	int		moves;
	int		quit;
}			t_data;

int			map(char *map_file, t_data *data);
int			free_map(t_map **map, int y);
int			key_handler(int keycode, t_data *data);
int			set_img(t_data *data);
void		set_data(t_data *data);
int			handle_expose(t_data *data);
void		draw_grid(t_data *data);
void		put_image_to_window(t_data *data, int x, int y, void *img);
int			check_feasable(t_map *location, int *chests, int *exit,
				t_map **map);
int			check_componants(t_data *data);
int			componants_error(t_data data, int i, int j);
int			check_wall(t_data data);
int			check_map_form(char *map_file, t_data data);
void		ft_string_put(t_data *data);
void		moove_exit(t_data *data);

#endif
