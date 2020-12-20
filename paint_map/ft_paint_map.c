/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 19:19:50 by scolen            #+#    #+#             */
/*   Updated: 2020/12/20 23:42:03 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_mms/mlx.h"
#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include "../cube3D.h"

typedef struct  s_window {
    void        *mlx;
    void        *win;
}               t_window;

int				key_hook(int keycode, t_window *window)
{
	printf("keycode: %d\n", keycode);
	if (keycode == 53)
		exit(1);
	(void)window;
	// printf("Hello from key_hook\n");
	return (1);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	filling_struct(t_data *img, void *mlx, int x, int y)
{
	img->img = mlx_new_image(mlx, x, y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian);
}

void	paint_map(char **map, t_value_from_map *value_map)
{
	int i;
	int j;
	int x;
	int y;

	t_data img_wall;
	t_data img_player;
	t_window window;
	(void)map;

	i = 0;
	j = 0;
	x = 60;
	y = 60;
	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, value_map->resolution_x, value_map->resolution_y, "Cube3D");
	filling_struct(&img_wall, window.mlx, x, y);
	filling_struct(&img_player, window.mlx, x, y);
	// img_wall.img = mlx_new_image(mlx, x, y);
	// img_wall.addr = mlx_get_data_addr(img_wall.img, &img_wall.bits_per_pixel,
	// 	&img_wall.line_length, &img_wall.endian);
	while (i < x)
	{
		while (j < y)
		{
			my_mlx_pixel_put(&img_wall, i, j, 0xFFFFFF);
			my_mlx_pixel_put(&img_player, i, j, 0xff0000);
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	j = 0;
	// mlx_put_image_to_window(mlx, win, img.img, 10, 10);
	while (map[i])
	{
		while (map[i][j])
		{
			// if (map[i][j] == ' ' || map[i][j] == '\t')
			// 	x = x + 10;
			// if (map[i][j] == 'N')
			// 	x = x + 10;
			// if (map[i][j] == '2')
			// 	x = x + 10;
			if (map[i][j] == '1')
			{
				mlx_put_image_to_window(window.mlx, window.win, img_wall.img, j * x, i * y);
				// x = x + 10;
			}
			if (map[i][j] == 'N')
			{
				mlx_put_image_to_window(window.mlx, window.win, img_player.img, j * x, i * y);
			}
			// if (map[i][j] == '0')
			// 	x = x + 10;
			j++;
		}
		// x = 10;
		// y = y + 10;
		j = 0;
		i++;
	}
	mlx_key_hook(window.win, key_hook, &window);
	mlx_loop_hook(window->mlx, ,); /// САМА ЗАНИМАЕТСЯ ПЕРЕРИСОВКОЙ!!!!!!
	mlx_loop(window.mlx);
}
