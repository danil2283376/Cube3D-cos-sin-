/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:14:38 by scolen            #+#    #+#             */
/*   Updated: 2020/12/16 20:45:23 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_mms/mlx.h"
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include "cube3D.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void	standart_value_struct(t_value_from_map *value_map)
{
	value_map->resolution_x = -1;
	value_map->resolution_y = -1;

	value_map->north_texture = NULL;
	value_map->south_texture = NULL;
	value_map->west_texture = NULL;
	value_map->east_texture = NULL;
	value_map->sprite_texture = NULL;

	value_map->floor_color_r = -1;
	value_map->floor_color_g = -1;
	value_map->floor_color_b = -1;

	value_map->ceilling_color_r = -1;
	value_map->ceilling_color_g = -1;
	value_map->ceilling_color_b = -1;
}

int main()
{
	int fd = open("map.cub", O_RDONLY);
	t_value_from_map *value_map;
	value_map = malloc(sizeof(t_value_from_map) * 1);
	standart_value_struct(value_map);
	manage_function(fd, value_map);
	return (0);
}

// int main()
// {
// 	int x = 30;
// 	int y = 30;
// 	void *mlx = NULL;
// 	void *window = NULL;
// 	int len_strng;
// 	int count_len;
// 	t_list *list_map;
// 	int start;
// 	int start_string;
// 	char *string;
// 	t_min_max_value min_max_value;

// 	start = 0;
// 	min_max_value.x_min = 30;
// 	start_string = 0;
// 	list_map = add_map(list_map);
// 	// while (list_map)
// 	// {
// 	// 	printf("%s\n", list_map->content);
// 	// 	list_map = list_map->next;
// 	// }
// 	count_len = ft_lstsize(list_map);
// 	// printf("\ncount_len: %d\n", count_len);
// 	mlx = mlx_init();
// 	window = mlx_new_window(mlx, 640, 480, "Cube3D");
// 	while (start < count_len && list_map)
// 	{
// 		// (char *)list_map->content[start_string]
// 		string = (char *)list_map->content;
// 		while (string[start_string] == '1')
// 		{
// 			printf("%d\n", 1);
// 			while (y++ < 50)
// 			{
// 				x = 30;
// 				while (x++ < 50)
// 				{
// 					mlx_pixel_put(mlx, window, x, y, 0xFFFFFF);
// 				}
// 			}
// 			y = 30;
// 			start_string++;
// 		}
// 		start_string = 0;
// 		list_map = list_map->next;
// 		start++;
// 	}
// 	printf("END\n");
// 	mlx_loop(mlx);
// 	return (0);
// }
