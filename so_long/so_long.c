/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:01 by almeddah          #+#    #+#             */
/*   Updated: 2025/01/20 18:51:50 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_close(t_data *data)
{
	data->quit = 1;
	return (0);
}

// char	*ft_strrchr(const char *s, int c)
// {
// 	char	*result;

// 	result = 0;
// 	while (*s)
// 	{
// 		if (*s == (char)c)
// 			result = (char *)s;
// 		s++;
// 	}
// 	if ((char)c == '\0')
// 		result = (char *)s;
// 	return (result);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!n)
// 		return (0);
// 	while (s1[i] && i < n - 1)
// 	{
// 		if (s1[i] != s2[i])
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 		i++;
// 	}
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

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
