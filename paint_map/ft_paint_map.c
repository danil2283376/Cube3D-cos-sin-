/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 19:19:50 by scolen            #+#    #+#             */
/*   Updated: 2020/12/21 13:34:30 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_mms/mlx.h"
#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include "../cube3D.h"

int				key_hook(int keycode, t_window *window)
{
	printf("keycode: %d\n", keycode);
	if (keycode == 53)
		exit(1);
	(void)window;
	// printf("Hello from key_hook\n");
	return (1);
}

void            my_mlx_pixel_put(t_info_image *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


//					данные о картинке цвет заполняемой картинки, и ширина и высота картинки
void	filling_image(t_info_image *img, int color, int x, int y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	img->x = x;
	img->y = y;
	img->img = mlx_new_image(img->mlx, img->x, img->y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian);
	while (i < img->x)
	{
		while (j < img->y)
		{
			my_mlx_pixel_put(img, i, j, color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	rebuilding_map(char **map, t_window *window, t_object_on_scene *objects)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == '1')
				mlx_put_image_to_window(window->mlx, window->win, objects->wall.img, j * objects->wall.x, i * objects->player.y);
			if (map[i][j] == 'N')
				mlx_put_image_to_window(window->mlx, window->win, objects->player.img, j * objects->player.x, i * objects->player.x);
			j++;
		}
		j = 0;
		i++;
	}
}

void	paint_map(char **map, t_value_from_map *value_map)
{
	int i;
	int j;
	int x;
	int y;

	t_info_image img_wall;
	t_info_image img_player;
	t_object_on_scene objects;
	t_window window;
	(void)map;

	i = 0;
	j = 0;
	x = 40;
	y = 40;
	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, value_map->resolution_x, value_map->resolution_y, "Cube3D");
	img_wall.mlx = window.mlx;
	img_player.mlx = window.mlx;
	filling_image(&img_wall, value_map->ceilling_color_r, x, y);
	filling_image(&img_player, value_map->ceilling_color_g, x, y);
	objects.player = img_player;
	objects.wall = img_wall;
	rebuilding_map(map, &window, &objects);
	mlx_key_hook(window.win, key_hook, &window);
	// mlx_loop_hook(window->mlx, ,); /// САМА В бесконечном цикле будет вызывать нашу функцию!!!!!!
	mlx_loop(window.mlx);
}
