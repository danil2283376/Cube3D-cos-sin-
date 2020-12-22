/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 19:19:50 by scolen            #+#    #+#             */
/*   Updated: 2020/12/22 20:16:50 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_mms/mlx.h"
#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include "../cube3D.h"
#include <math.h>

#pragma region movent_player
void				move_left(t_object_on_scene *obj)
{
	if (obj->map[obj->player_y][obj->player_x - 1] != '1')
	{
		int i;
		int j;
		int new_pos;

		i = obj->player_y - 1;
		j = obj->player_x;
		new_pos = obj->player.height_y;
		printf("new_pos: %d\n", new_pos);
		while ('1' != obj->map[i][j])
		{
			write(1, "2", 1);
			printf("pos_ray: x = %d, y = %d\n", j, i);
			mlx_put_image_to_window(obj->mlx, obj->win, obj->floor.img, (obj->player_x * obj->player.width_x), ((obj->player_y) * (obj->player.height_y) - new_pos));
			new_pos = new_pos + (obj->player.height_y);
			i--;
		}
		obj->map[obj->player_y][obj->player_x] = '0';
		printf("pos: x = %d, y = %d\n", j, i);
		mlx_put_image_to_window(obj->mlx, obj->win, obj->floor.img, (obj->player_x * obj->player.width_x), obj->player_y * obj->player.height_y);
		// mlx_put_image_to_window(obj->mlx, obj->win, obj->floor.img, obj->player_y * obj->player.x, obj->player_x * obj->player.y);
		obj->map[obj->player_y][obj->player_x - 1] = 'N';
	}
}

void			move_right(t_object_on_scene *obj)
{
	int i;
	int j;
	int new_pos;

	i = obj->player_y - 1;
	j = obj->player_x;
	new_pos = obj->player.height_y;;
	if (obj->map[obj->player_y][obj->player_x + 1] != '1')
	{
		obj->map[obj->player_y][obj->player_x] = '0';
		mlx_put_image_to_window(obj->mlx, obj->win, obj->floor.img, (obj->player_x * obj->player.width_x), obj->player_y * obj->player.height_y);
		while ('1' != obj->map[i][j])
		{
			write(1, "2", 1);
			printf("pos_ray: x = %d, y = %d\n", j, i);
			mlx_put_image_to_window(obj->mlx, obj->win, obj->floor.img, (obj->player_x * obj->player.width_x), ((obj->player_y) * (obj->player.height_y) - new_pos));
			new_pos = new_pos + (obj->player.height_y);
			i--;
		}
		obj->map[obj->player_y][obj->player_x + 1] = 'N';
	}
}

void			move_top(t_object_on_scene *obj)
{
	if (obj->map[obj->player_y - 1][obj->player_x] != '1')
	{
		obj->map[obj->player_y][obj->player_x] = '0';
		mlx_put_image_to_window(obj->mlx, obj->win, obj->floor.img, (obj->player_x * obj->player.width_x), obj->player_y * obj->player.height_y);
		obj->map[obj->player_y - 1][obj->player_x] = 'N';
	}
}

void			move_down(t_object_on_scene *obj)
{
	if (obj->map[obj->player_y + 1][obj->player_x] != '1')
	{
		obj->map[obj->player_y][obj->player_x] = '0';
		mlx_put_image_to_window(obj->mlx, obj->win, obj->floor.img, (obj->player_x * obj->player.width_x), obj->player_y * obj->player.height_y);
		obj->map[obj->player_y + 1][obj->player_x] = 'N';
	}
}
#pragma endregion

int				key_hook(int keycode, t_object_on_scene *obj)
{
	printf("keycode: %d\n", keycode);
	if (keycode == 53)
		exit(1);
	if (/*keycode == 123 ||*/ keycode == 0) // лево
		move_left(obj);
	if (/*keycode == 124 || */keycode == 2) // вправо
		move_right(obj);
	if (/*keycode == 126 || */keycode == 13) // вверх
		move_top(obj);
	if (/* keycode == 125 || */keycode == 1) // вниз
		move_down(obj);

	(void)obj;
	// printf("Hello from key_hook\n");
	return (1);
}

void            my_mlx_pixel_put(t_info_image *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void	filling_image_ray(t_info_image *img, int color, int x, int y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	img->width_x = x;
	img->height_y = y;
	img->img = mlx_new_image(img->mlx, 1/*img->width_x*/, img->height_y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian);
	while (i < 5)
	{
		while (j < y)
		{
			my_mlx_pixel_put(img, i, j, color);
			j++;
		}
		// i = 19;
		i++;
	}
}

//					данные о картинке цвет заполняемой картинки, и ширина и высота картинки
void	filling_image(t_info_image *img, int color, int x, int y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	img->width_x = x;
	img->height_y = y;
	img->img = mlx_new_image(img->mlx, img->width_x, img->height_y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian);
	while (i < img->width_x)
	{
		while (j < img->height_y)
		{
			my_mlx_pixel_put(img, i, j, color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	raycast(t_object_on_scene *objects, int i_ray, int j_ray)
{
	// objects->start = objects->player_dir - M_PI_4;
	// objects->end = objects->player_dir + M_PI_4;
	// while (objects->start < objects->end)
	// {
	// 	while (objects->map[(int)(objects->player_y / SCALE)][])
	// 	{

	// 	}
	// }
	while (objects->map[i_ray][j_ray] != '1' && i_ray >= 0)
	{
		// write(1, "1", 1);
		mlx_put_image_to_window(objects->mlx, objects->win, objects->ray.img, (j_ray * objects->ray.width_x) + (objects->player.width_x / 2), i_ray * objects->ray.height_y);
		i_ray--;
	}
}

int	rebuilding_map(/*char **map, t_window *window, */t_object_on_scene *objects)
{
	int i;
	int j;
	int i_ray;
	int j_ray;
	static int boolean = 0;

	i = 0;
	j = 0;
	while (objects->map[i])
	{
		while (objects->map[i][j])
		{
			if (objects->map[i][j] == '1')
				mlx_put_image_to_window(objects->mlx, objects->win, objects->wall.img, j * objects->wall.width_x, i * objects->player.height_y);
			if (objects->map[i][j] == 'N')
			{
				objects->player_x = j; // позиция по х
				objects->player_y = i; // позиция по y
				i_ray = i;
				j_ray = j;
				raycast(objects, i_ray, j_ray);
				// while (objects->map[i_ray][j_ray] != '1' && i_ray >= 0)
				// {
				// 	// write(1, "1", 1);
				// 	mlx_put_image_to_window(objects->mlx, objects->win, objects->ray.img, j_ray * objects->ray.width_x, i_ray * objects->ray.height_y);
				// 	i_ray--;
				// }
				mlx_put_image_to_window(objects->mlx, objects->win, objects->player.img, j * objects->player.width_x, i * objects->player.height_y);
			}
			if (objects->map[i][j] == '0' && boolean == 0)
				mlx_put_image_to_window(objects->mlx, objects->win, objects->floor.img, j * objects->floor.width_x, i * objects->floor.height_y);
			j++;
		}
		j = 0;
		i++;
	}
	boolean = 1;
	return (0);
}

int	filling_color(t_object_on_scene *obj, t_value_from_map *value_map, char obj_on_scene)
{
	int color_hex;

	color_hex = 0;
	if (obj_on_scene == 'N')
	{
		color_hex = 10 | 50 | 100;
		obj->player.color = color_hex;
	}
	if (obj_on_scene == '1')
	{
		color_hex = 0xf3f2ff;
		obj->wall.color = color_hex;
	}
	if (obj_on_scene == '0')
	{
		color_hex = value_map->ceilling_color_r | value_map->ceilling_color_g | value_map->ceilling_color_b;
		obj->floor.color = color_hex;
	}
	return (color_hex);
}



int	raycasting(t_object_on_scene *obj)
{
	int i;
	int j;

	j = obj->player_x;
	i = obj->player_y;
	// while (1)
	// {
		printf("player_position x= %d, y= %d\n", j, i);
		write(1, "1", 1);
		// while (obj->map[i])
		// {
		// 	while (obj->map[i][j] != '1')
		// 	{
		// 		mlx_put_image_to_window(obj->mlx, obj->win, obj->player.img, j * obj->player.x, i * obj->player.y);
		// 	}
		// }
		// while ('1' != obj->map[y][x])
		// {
			// write(1, "1", 1);
			// mlx_put_image_to_window(obj->mlx, obj->win, obj->ray.img, x * obj->player.x, y * obj->player.y);
			// y = y - 1;
			// y = y + (obj->player_y);
		// }
		// y = (obj->player_y);
	// }
	return (1);
}

void	paint_map(char **map, t_value_from_map *value_map)
{
	int x;
	int y;

	t_info_image img_wall;
	t_info_image img_player;
	t_info_image img_floor;
	t_info_image img_ray;
	t_object_on_scene objects;
	t_window window;

	x = 70;
	y = 70;
	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, value_map->resolution_x, value_map->resolution_y, "Cube3D");
	img_wall.mlx = window.mlx;
	img_player.mlx = window.mlx;
	img_floor.mlx = window.mlx;
	img_ray.mlx = window.mlx;
	filling_image(&img_wall, filling_color(&objects, value_map, '1'), x, y);
	filling_image(&img_player, filling_color(&objects, value_map, 'N'), x, y);
	filling_image(&img_floor, /*filling_color(&objects, value_map, '0')*/0x808080, x, y);
	filling_image_ray(&img_ray, 0xff0000, x, y);
	objects.player = img_player;
	objects.plyer_dir = 90;
	objects.wall = img_wall;
	objects.floor = img_floor;
	objects.ray = img_ray;
	objects.map = map;
	objects.mlx = window.mlx;
	objects.win = window.win;
	// rebuilding_map(/*map, &window, */&objects);
	// mlx_key_hook(window.win, key_hook, &objects);
	// mlx_expose_hook(,);
	write(1, "1", 1);
	rebuilding_map(/*char **map, t_window *window, */&objects);
	mlx_hook(window.win, 2, 1L << 0, key_hook, &objects);
	mlx_loop_hook(window.mlx, rebuilding_map, &objects);
	// mlx_loop_hook(window.mlx, raycasting, &objects);
	// mlx_loop_hook(window.mlx, key_hook, &objects);
	// mlx_loop_hook(window.mlx, mlx_key_hook(window.mlx, key_hook, &objects)/*rebuilding_map*/, &objects);
	// mlx_mouse_hook(window.win, key_hook, &window);
	// mlx_loop_hook(window->mlx, ,); /// САМА В бесконечном цикле будет вызывать нашу функцию!!!!!!
	mlx_loop(window.mlx);
}
