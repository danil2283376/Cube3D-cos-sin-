/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:13:51 by scolen            #+#    #+#             */
/*   Updated: 2020/12/27 15:01:29 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_mms/mlx.h"
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

typedef	struct	s_value_from_map
{
	int			resolution_x;
	int			resolution_y;

	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*sprite_texture;

	int			floor_color_r;
	int			floor_color_g;
	int			floor_color_b;

	int			ceilling_color_r;
	int			ceilling_color_g;
	int			ceilling_color_b;
}				t_value_from_map;

typedef struct  s_info_image
{
	void		*mlx;
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int			endian;
	int			width_x;
	int			height_y;
	int			color;
}               t_info_image;

typedef struct s_object_on_scene
{
	t_info_image	player;
	float			player_position_x;
	float			player_position_y;
	float			player_direction_x;
	float			player_direction_y;
	float			player_angle;
	// float			player_angle_right;
	int				speed;

	t_info_image floor;
	t_info_image wall;
	t_info_image prize;
	t_info_image ray;
	float		position_ray_x;
	float		position_ray_y;
	float		min_angle;
	float		max_angle;
	char		**map;
	void		*mlx;
	void        *win;

}				t_object_on_scene;

int			len_number(int number);
int			ft_strcmp(const char *str1, const char *str2);
int			pass_space(char *substr);
int			count_comma(char *substr);
void		get_value_resolution(char *line, t_value_from_map *value_map);
void		get_path_sprite(char *line, t_value_from_map *value_map);
void		get_path_east(char *line, t_value_from_map *value_map);
void		get_path_north(char *line, t_value_from_map *value_map);
void		get_path_south(char *line, t_value_from_map *value_map);
void		get_path_west(char *line, t_value_from_map *value_map);
void		get_value_color(char *line, t_value_from_map *value_map);
void		get_value_color_floor(char *line, t_value_from_map *value_map);
void		standart_value_struct(t_value_from_map *value_map);
int			value_from_maps_not_null(t_value_from_map *value_map);
void		paint_map(char **map, t_value_from_map *value_map);
char		**manage_function(int fd, t_value_from_map *value_map);
