/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 19:19:50 by scolen            #+#    #+#             */
/*   Updated: 2021/01/03 16:36:43 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_mms/mlx.h"
#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include "../cube3D.h"

void            my_mlx_pixel_put(t_info_image *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

//					данные о картинке цвет заполняемой картинки, и ширина и высота картинки
void	filling_image(t_info_image *img/*, int color*/, int x, int y)
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
}

void	raycast(t_object_on_scene *objects)
{
	float	save_x;
	float	save_y;
	float	length_ray;

	t_object_on_scene ray = *objects;
	ray.player_position_x += (objects->player_direction_x);
	ray.player_position_y += (objects->player_direction_y);
	save_x = ray.player_position_x;
	save_y = ray.player_position_y;
	ray.min_angle = ray.player_angle - 45;
	ray.max_angle = ray.player_angle + 45;
	objects->ray_min_angle = ray.min_angle;
	objects->ray_max_angle = ray.max_angle;
	length_ray = 0.0;
	int size_x = 1920;
	int size_y = 1080;
	int length_eye = 0;
	int new_len_ray = 0;
	while (ray.min_angle < ray.max_angle)
	{
		ray.player_position_x = save_x;
		ray.player_position_y = save_y;
		while (objects->map[(int)ray.player_position_y][(int)(ray.player_position_x)] != '1' && length_eye < 100000)
		{
			//позиция игрока		старая позиция игрока +
			ray.player_position_x = ray.player_position_x + length_ray * cos(ray.min_angle * (M_PI / 180.0));
			ray.player_position_y = (ray.player_position_y + length_ray * ((sin(ray.min_angle * (M_PI / 180.0)) * (-1))));

			my_mlx_pixel_put(&objects->window, ((/*objects->player.width_x*/objects->width_bloks_x * ray.player_position_x)/* + (objects->player.width_xobjects->width_bloks_x / 2)*/),
			((/*objects->player.height_y*/objects->height_bloks_y * ray.player_position_y))/* + 35*/, 0xffff00);
			length_ray = length_ray + 0.0001;
			// printf("ray.min_angle: %f\n", ray.min_angle);
			// printf("ray.player_angle: %f\n", ray.player_angle);
			// if ((int)ray.min_angle == (int)ray.player_angle)
				new_len_ray = new_len_ray + 1;
			length_eye++;
			// printf("Длина луча в пикселях: %f\n", length_ray);
		}
		length_eye = 0;
		int length_wall;
		length_wall = 0;
		printf("new_len_ray: %d\n", new_len_ray);
		float top_wall = ((size_y / 2) * (1.0 - (1.0 / new_len_ray * 100)));
		float down_wall = ((size_y / 2) * (1.0 + (1.0 / new_len_ray * 100)));
		printf("top_wall: %f\n", top_wall);
		printf("down_wall: %f\n", down_wall);
		while (down_wall > top_wall)
		{
			// printf("Низ стены: %f, Вверх стены: %f\n", down_wall, top_wall);
			my_mlx_pixel_put(&objects->window, size_x, down_wall, 0xffff00);
			down_wall--;
		}
		size_x = size_x - 10;
		// write(1, "SOS\n", 4);
		// float start = 0.0;
		// float lenght_wall = 300;
		// // printf("lenght_ray: %f\n", length_ray);
		// while ((float)start < ((float)lenght_wall / (float)length_ray))
		// {
		// 	// int answer = lenght_wall / length_ray;
		// 	// printf("answer: %d\n", answer);
		// 	printf("start: %f < %f\n", start, (lenght_wall / (int)length_ray));
		// 	my_mlx_pixel_put(&objects->window,
		// 	cos(ray.min_angle * (M_PI / 180.0)) + size_x,
		// 	(sin(ray.min_angle * (M_PI / 180.0))) + size_y - start, 0xffff00);
		// 	start = start + 0.1;
		// }
		// // // bring = 0;
		length_ray = 0;
		new_len_ray = 0;
		// size_x = size_x + 10;
		ray.min_angle = ray.min_angle + 0.5;
	}
	// рабочий луч
	// while (objects->map[i_ray][j_ray] != '1' && i_ray >= 0)
	// {
	// 	mlx_put_image_to_window(objects->mlx, objects->win, objects->ray.img, (j_ray * objects->ray.width_x) + (objects->player.width_x / 2), i_ray * objects->ray.height_y);
	// 	i_ray--;
	// }
}

void	filling_exist_image(t_object_on_scene *obj, float i, float j, int color)
{
	int x;
	int y;
	int width;
	int height;

	x = 0;
	y = 0;
	width = obj->width_bloks_x;
	height = obj->height_bloks_y;
	while (y < height)
	{
		while (x < width)
		{
			my_mlx_pixel_put(&obj->window, (j * width) + x, (i * height) + y, color);
			x++;
		}
		x = 0;
		y++;
	}
}

int	rebuilding_map(t_object_on_scene *objects)
{
	float i;
	float j;
	static int boolean = 0;

	i = 0.0;
	j = 0.0;
	while (objects->map[(int)i])
	{
		while (objects->map[(int)i][(int)j])
		{
			if (objects->map[(int)i][(int)j] == '1')
				filling_exist_image(objects, i, j, 0xffffff);
			if (objects->map[(int)i][(int)j] == 'N')
			{
				objects->player_position_x = j;
				objects->player_position_y = i;
				if (boolean == 0)
				{
					objects->position_ray_x = objects->player_position_x;
					objects->position_ray_y = objects->player_position_y;
				}
				raycast(objects);
			}
			if (objects->map[(int)i][(int)j] == '0')
				filling_exist_image(objects, i, j, 0x808080);
			j++;
		}
		j = 0;
		i++;
	}
	boolean = 1;
	return (0);
}

void			move(t_object_on_scene *obj)
{
	printf("x: %f, y: %f\n", obj->player_direction_x, obj->player_direction_y);
	mlx_put_image_to_window(obj->mlx, obj->win, obj->player.img,
	(obj->player_position_x * obj->player.width_x) + (obj->player_direction_x * (obj->speed * 2)), // по x
	obj->player_position_y * obj->player.height_y + (obj->player_direction_y * (obj->speed * 2))); // по y
}

void			not_wall(t_object_on_scene *obj)
{
	t_object_on_scene ray = *obj;
	int		deg;
	float	x;
	float	y;

	obj->top_ray = 0;
	obj->down_ray = 0;
	obj->left_ray = 0;
	obj->right_ray = 0;
	deg = 0;
	ray.player_position_x += obj->player_direction_x;
	ray.player_position_y += obj->player_direction_y;
	x = ray.player_position_x;
	y = ray.player_position_y;

	while (deg < 360)
	{
		ray.player_position_x = x;
		ray.player_position_y = y;
		while (obj->map[(int)ray.player_position_y][(int)ray.player_position_x] != '1')
		{
			ray.player_position_x = ray.player_position_x + (cos(deg * (M_PI / 180.0)));
			ray.player_position_y = ray.player_position_y+ (sin(deg * (M_PI / 180.0)) * -1);
			if (deg == obj->player_angle + 90)
				obj->left_ray++;
			if (deg == obj->player_angle - 90)
				obj->right_ray++;
			if (deg == obj->player_angle)
				obj->top_ray++;
			if (deg == obj->player_angle + 180)
				obj->down_ray++;
		}
		deg++;
	}
}

int				key_hook(int keycode, t_object_on_scene *obj)
{
	if (keycode == 53)
		exit(1);
	float move_x = (cos(obj->player_angle * (M_PI / 180.0))) * (-1);
	float move_y = (sin(obj->player_angle * (M_PI / 180.0))) * (-1);
		// поворот градусов
	if (keycode == 123)
		obj->player_angle = obj->player_angle + 2.0;
	if (keycode == 124)
		obj->player_angle = obj->player_angle - 2.0;
	if (/*keycode == 123 ||*/ keycode == 0/* && obj->left_ray != 0.0*/) // лево
	{
		obj->player_direction_x += cos((obj->ray_max_angle + 45) * (M_PI / 180.0)) / 7;
		obj->player_direction_y += sin((obj->ray_max_angle + 45) * (M_PI / 180.0)) * (-1) / 7;
	}
	if (/*keycode == 124 || */keycode == 2/* && obj->right_ray != 1.0*/) // вправо
	{
		obj->player_direction_x += cos((obj->ray_min_angle - 45) * (M_PI / 180.0)) / 7;
		obj->player_direction_y += sin((obj->ray_min_angle - 45) * (M_PI / 180.0)) * (-1) / 7;
		// float negative_y = move_y * (-1);
		// float varible =
	}
	if (/*keycode == 126 || */keycode == 13/* && obj->top_ray != 0.0*/) // вверх
	{
		obj->player_direction_x -= move_x / 7;
		obj->player_direction_y += move_y / 7;
	}
	if (/* keycode == 125 || */keycode == 1/* && obj->down_ray != 1.0*/) // вниз
	{
		obj->player_direction_x += move_x / 7;
		obj->player_direction_y -= move_y / 7;
	}
	rebuilding_map(obj);
	my_mlx_pixel_put(&obj->window,
	(obj->player_position_x * obj->width_bloks_x) + (obj->player_direction_x * (obj->speed / 2/* * 2*/)),
	obj->player_position_y * obj->height_bloks_y + (obj->player_direction_y * (obj->speed / 2/* * 2*/)), 0x00ff00);
	mlx_put_image_to_window(obj->mlx, obj->win, obj->window.img, 0, 0); // по y
	mlx_destroy_image(obj->mlx, obj->window.img);
	filling_image(&obj->window, 1920, 1080);
	return (1);
}

void	settings_objects(t_object_on_scene *objects)
{
	objects->floor.mlx = objects->mlx;
	objects->wall.mlx = objects->mlx;
	objects->prize.mlx = objects->mlx;
	objects->ray.mlx = objects->mlx;
	objects->player.mlx = objects->mlx;
	objects->window.mlx = objects->mlx;
}

void	set_settings_player(t_object_on_scene *objects)
{
	objects->player_angle = 90;
	objects->player_direction_x = 0.0;
	objects->player_direction_y = 0.0;
	objects->player_position_x = 0.0;
	objects->player_position_y = 0.0;
	objects->speed = 20;
}

void	paint_map(char **map, t_value_from_map *value_map)
{
	int x;
	int y;
	t_object_on_scene objects;

	x = 10;
	y = 10;
	objects.mlx = mlx_init();
	objects.win = mlx_new_window(objects.mlx, value_map->resolution_x, value_map->resolution_y, "Cube3D");
	objects.map = map;
	objects.width_bloks_x = x;
	objects.height_bloks_y = y;
	settings_objects(&objects);
	set_settings_player(&objects);
	filling_image(&objects.window, value_map->resolution_x, value_map->resolution_y);
	rebuilding_map(&objects);
	mlx_put_image_to_window(objects.mlx, objects.win, objects.window.img, 0, 0);
	mlx_hook(objects.win, 2, 1L << 0, key_hook, &objects);
	// write(1, "1", 1);
	// mlx_loop_hook(objects.mlx, rebuilding_map, &objects);
	// mlx_hook(objects.win, 2, 1L << 0, rebuilding_map, &objects);
	// mlx_loop_hook(window->mlx, ,); /// САМА В бесконечном цикле будет вызывать нашу функцию!!!!!!
	mlx_loop(objects.mlx);
}
