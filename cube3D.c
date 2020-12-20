/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:14:38 by scolen            #+#    #+#             */
/*   Updated: 2020/12/20 19:56:07 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_mms/mlx.h"
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include "cube3D.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("map.cub", O_RDONLY);
	char **map;
	t_value_from_map *value_map;

	value_map = malloc(sizeof(t_value_from_map) * 1);
	standart_value_struct(value_map);
	map = manage_function(fd, value_map);

	paint_map(map, value_map);
	printf("Resolution: x = %d, y = %d\n", value_map->resolution_x, value_map->resolution_y);
	printf("North = %s\n", value_map->north_texture);
	printf("South = %s\n", value_map->south_texture);
	printf("West = %s\n", value_map->west_texture);
	printf("East = %s\n", value_map->east_texture);
	printf("Sprite = %s\n", value_map->sprite_texture);
	printf("Color_r = %d\n", value_map->ceilling_color_r);
	printf("Color_g = %d\n", value_map->ceilling_color_g);
	printf("Color_b = %d\n", value_map->ceilling_color_b);
	printf("Floor_r = %d\n", value_map->floor_color_r);
	printf("Floor_g = %d\n", value_map->floor_color_g);
	printf("Floor_b = %d\n", value_map->floor_color_b);
	close(fd);
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
