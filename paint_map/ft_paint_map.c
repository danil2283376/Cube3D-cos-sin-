/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 19:19:50 by scolen            #+#    #+#             */
/*   Updated: 2020/12/27 20:23:21 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_mms/mlx.h"
#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include "../cube3D.h"
#include <math.h>

void	raycast(t_object_on_scene *objects)
{
	float	save_x;
	float	save_y;
	t_object_on_scene ray = *objects;
	ray.player_position_x += (objects->player_direction_x);
	ray.player_position_y += (objects->player_direction_y);
	save_x = ray.player_position_x;
	save_y = ray.player_position_y;
	// printf("dir_x: %f, dir_y: %f\n", objects->player_direction_x, objects->player_direction_y);
	ray.min_angle = ray.player_angle - 45;
	ray.max_angle = ray.player_angle + 45;
	while (ray.min_angle < ray.max_angle)
	{
		ray.player_position_x = save_x;
		ray.player_position_y = save_y;
		while (objects->map[(int)ray.player_position_y][(int)(ray.player_position_x)] != '1')
		{
			// printf("player{x:%f, y:%f} \t\t ray{x:%f, y:%f}\n",
			// objects->player_position_x, objects->player_position_y, ray.player_position_x, ray.player_position_y);
			//позиция игрока		старая позиция игрока +
			ray.player_position_x = ray.player_position_x + cos(ray.min_angle * (M_PI / 180.0));
			ray.player_position_y = (ray.player_position_y + ((sin(ray.min_angle * (M_PI / 180.0)) * (-1))));
			mlx_put_image_to_window(ray.mlx, ray.win, ray.ray.img,
			((objects->player.width_x * ray.player_position_x) + (objects->player.width_x / 2)),
			((objects->player.height_y * ray.player_position_y)) + 35);
			// i++;
		}
		ray.min_angle = ray.min_angle + 2.0;
		// ray.min_angle += ray.min_angle / 5;
		// ray.player_position_x = objects->player_position_x;
		// ray.player_position_y = objects->player_position_y;
	}
	// objects->position_ray_x = ray.player_position_x;
	// objects->position_ray_y = ray.player_position_y;
	// while (objects->map[(int)(ray.player_y / ray.player.width_x)][(int)(ray.player_x / ray.player.width_x)] != '1' && i < 5)
	// {
	// printf("player_angle: %f\n", objects->player_angle);

	// while (i < 5)
	// {
	// 	ray.player_position_x = ray.player_position_x + (cos(ray.player_angle * (M_PI / 180.0)));
	// 	ray.player_position_y = ray.player_position_y + (sin(ray.player_angle * (M_PI / 180.0)));
	// 	printf("player_pos_x: %f, player_pos_y: %f\n", ray.player_position_x, ray.player_position_y);
	// 	ray.player_position_y *= (-1);
	// 	mlx_put_image_to_window(ray.mlx, ray.win, ray.ray.img,
	// 	(objects->player_position_x * objects->player.width_x + (objects->player.width_x / 2)) + (ray.player_position_x * objects->player.width_x),
	// 	(objects->player_position_y * objects->player.height_y) + (ray.player_position_y * objects->player.height_y));
	// 	i++;
	// }


	// ray.player_position_x = cos(ray.player_angle * (M_PI / 180.0));
	// ray.player_position_y = sin(ray.player_angle * (M_PI / 180.0));
	// printf("x: %f, y: %f\n", ray.player_position_x, ray.player_position_y);
	// mlx_put_image_to_window(ray.mlx, ray.win, ray.ray.img,
	// 	(objects->player_position_x * objects->player.width_x + (objects->player.width_x / 2 )) + (ray.player_position_x * objects->player.width_x),
	// 	 (objects->player_position_y * objects->player.height_y) + (ray.player_position_y * objects->player.height_y));

	// рабочий луч
	// while (objects->map[i_ray][j_ray] != '1' && i_ray >= 0)
	// {
	// 	mlx_put_image_to_window(objects->mlx, objects->win, objects->ray.img, (j_ray * objects->ray.width_x) + (objects->player.width_x / 2), i_ray * objects->ray.height_y);
	// 	i_ray--;
	// }
}

int	rebuilding_map(t_object_on_scene *objects)
{
	float i;
	float j;
	static int boolean = 0;
	(void)objects;
	i = 0.0;
	j = 0.0;
	mlx_clear_window(objects->mlx, objects->win);
	while (objects->map[(int)i])
	{
		while (objects->map[(int)i][(int)j])
		{
			if (objects->map[(int)i][(int)j] == '1')
				mlx_put_image_to_window(objects->mlx, objects->win, objects->wall.img, j * objects->wall.width_x, i * objects->player.height_y);
			if (objects->map[(int)i][(int)j] == 'N')
			{
				objects->player_position_x = j;
				objects->player_position_y = i;
				if (boolean == 0)
				{
					objects->position_ray_x = objects->player_position_x;
					objects->position_ray_y = objects->player_position_y;
				}
				// if (objects->map[(int)objects->position_ray_y][(int)objects->position_ray_y] != '1')
				// {
				// printf("{x: %d, y: %d}\n", (int)objects->position_ray_x, (int)objects->position_ray_y);
				// }
				raycast(objects);
			}
			if (objects->map[(int)i][(int)j] == '0' && boolean == 0)
				mlx_put_image_to_window(objects->mlx, objects->win, objects->floor.img, j * objects->floor.width_x, i * objects->floor.height_y);
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

int				key_hook(int keycode, t_object_on_scene *obj)
{
	// if ((int)obj->player_angle > 360 || (int)obj->player_angle < -360)
	// 	obj->player_angle = 0;
	// if ((int)obj->player_angle_right >)
	// printf("keycode: %d\n", keycode);
	if (keycode == 53)
		exit(1);
		// поворот градусов
	if (keycode == 123)
		obj->player_angle = obj->player_angle + 20.0;
	if (keycode == 124)
		obj->player_angle = obj->player_angle - 20.0;
	float move_x = (cos(obj->player_angle * (M_PI / 180.0))) * (-1);
	float move_y = (sin(obj->player_angle * (M_PI / 180.0))) * (-1);
	// if (/*keycode == 123 ||*/ keycode == 0) // лево
	// {
	// 	obj->player_direction_x -= move_x;
	// }
	if (/*keycode == 124 || */keycode == 2) // вправо
	{
		obj->player_direction_x += cos(0);
		obj->player_direction_y += sin(0); // доделать в право и в лево
	}
	if (/*keycode == 126 || */keycode == 13) // вверх
	{
		obj->player_direction_x -= move_x;
		obj->player_direction_y += move_y;
	}
	if (/* keycode == 125 || */keycode == 1) // вниз
	{
		obj->player_direction_x += move_x;
		obj->player_direction_y -= move_y;
	}
	// printf("Hello from key_hook\n");
	// move(obj);
	printf("до move: x: %f, y: %f\n", move_x, move_y);
	rebuilding_map(obj);
	mlx_put_image_to_window(obj->mlx, obj->win, obj->player.img,
	(obj->player_position_x * obj->player.width_x) + (obj->player_direction_x * (obj->speed * 2)), // по x
	obj->player_position_y * obj->player.height_y + (obj->player_direction_y * (obj->speed * 2))); // по y
	// move(obj);
	return (1);
}

void            my_mlx_pixel_put(t_info_image *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
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

void	settings_objects(t_object_on_scene *objects)
{
	objects->floor.mlx = objects->mlx;
	objects->wall.mlx = objects->mlx;
	objects->prize.mlx = objects->mlx;
	objects->ray.mlx = objects->mlx;
	objects->player.mlx = objects->mlx;
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

	x = 40;
	y = 40;
	objects.mlx = mlx_init();
	objects.win = mlx_new_window(objects.mlx, value_map->resolution_x, value_map->resolution_y, "Cube3D");
	objects.map = map;
	settings_objects(&objects);
	set_settings_player(&objects);
	filling_image(&objects.wall, 0xffffff, x, y);
	filling_image(&objects.player, 0x00ff00, x, y);
	filling_image(&objects.floor, 0x808080, x, y);
	filling_image(&objects.ray, 0xffff00, 3, 3);
	rebuilding_map(&objects);
	mlx_hook(objects.win, 2, 1L << 0, key_hook, &objects);
	// mlx_loop_hook(objects.mlx, rebuilding_map, &objects);
	// mlx_hook(objects.win, 2, 1L << 0, rebuilding_map, &objects);
	// mlx_loop_hook(window->mlx, ,); /// САМА В бесконечном цикле будет вызывать нашу функцию!!!!!!
	mlx_loop(objects.mlx);
}
