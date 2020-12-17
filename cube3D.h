/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:13:51 by scolen            #+#    #+#             */
/*   Updated: 2020/12/16 20:41:23 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_mms/mlx.h"
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

typedef	struct	s_min_max_value
{
	int x_min;
	int x_max;
	int y_min;
	int y_max;
}				t_min_max_value;

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

void	manage_function(int fd, t_value_from_map *value_map);
