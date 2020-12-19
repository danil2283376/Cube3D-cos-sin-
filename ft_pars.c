/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:15:09 by scolen            #+#    #+#             */
/*   Updated: 2020/12/19 22:56:02 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_mms/mlx.h"
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include "cube3D.h"

int	len_number(int number)
{
	int len;

	len = 1;
	if (number < 0)
		number = number * (-1);
	while (number > 0)
	{
		number = number / 10;
		len++;
	}
	return (len);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)str1;
	ptr2 = (unsigned char *)str2;
	i = 0;
	while (str1[i] && str2[i])
	{
		if (ptr1[i] == ptr2[i])
			i++;
		else if (ptr1[i] > ptr2[i])
			return (ptr1[i] - ptr2[i]);
		else
			return (ptr2[i] - ptr1[i]);
	}
	return (0);
}

int		pass_space(char *substr)
{
	int start;

	start = 0;
	while (substr[start] == ' ' || substr[start] == '\t')
		start++;
	return (start);
}

int	count_comma(char *substr)
{
	int start;
	int count_comma;

	start = 0;
	count_comma = 0;
	while (substr[start])
	{
		if (substr[start] == ',')
			count_comma++;
		start++;
	}
	return (count_comma);
}

#pragma region path_sprite

int	get_path_sprite(char *line, t_value_from_map *value_map)
{
	char *substr;
	int start;
	static int quantity_s = 0;

	substr = ft_strnstr(line, "S", ft_strlen(line));
	start = 0;
	if (NULL != substr && ft_strncmp(substr, "S", 2))
	{
		quantity_s++;
		if (quantity_s == 2)
		{
			start = start + 2;
			while (substr[start] == ' ' && substr[start])
				start++;
			value_map->sprite_texture = ft_strdup(&substr[start]);
			while (substr[start] != ' ' && substr[start]
				!= '\t' && substr[start])
				start++;
			if (substr[start] == ' ' || substr[start] == '\t')
				value_map->sprite_texture = NULL;
		}
		else if (quantity_s > 2)
			value_map->sprite_texture = NULL;
	}
	return (quantity_s);
}

int	get_path_east(char *line, t_value_from_map *value_map)
{
	char *substr;
	int start;
	static int quantity_ea = 0;

	substr = ft_strnstr(line, "EA", ft_strlen(line));
	start = 0;
	if (NULL != substr && ft_strncmp(substr, "EA", 3))
	{
		quantity_ea++;
		if (quantity_ea == 1)
		{
			start = start + 2;
			while (substr[start] == ' ' && substr[start])
				start++;
			value_map->east_texture = ft_strdup(&substr[start]);
			while (substr[start] != ' ' && substr[start]
				!= '\t' && substr[start])
				start++;
			if (substr[start] == ' ' || substr[start] == '\t')
				value_map->east_texture = NULL;
		}
		else
			value_map->east_texture = NULL;
	}
	return (quantity_ea);
}

int	get_path_west(char *line, t_value_from_map *value_map)
{
	char *substr;
	int start;
	static int quantity_we = 0;

	substr = ft_strnstr(line, "WE", ft_strlen(line));
	start = 0;
	if (NULL != substr && ft_strncmp(substr, "WE", 3))
	{
		quantity_we++;
		if (quantity_we == 1)
		{
			start = start + 2;
			while (substr[start] == ' ' && substr[start])
				start++;
			value_map->west_texture = ft_strdup(&substr[start]);
			while (substr[start] != ' ' && substr[start]
				!= '\t' && substr[start])
				start++;
			if (substr[start] == ' ' || substr[start] == '\t')
				value_map->west_texture = NULL;
		}
		else
			value_map->west_texture = NULL;
	}
	return (quantity_we);
}

int	get_path_south(char *line, t_value_from_map *value_map)
{
	char *substr;
	int start;
	static int quantity_so = 0;

	substr = ft_strnstr(line, "SO", ft_strlen(line));
	start = 0;
	if (NULL != substr && ft_strncmp(substr, "SO", 3))
	{
		quantity_so++;
		if (quantity_so == 1)
		{
			start = start + 2;
			while (substr[start] == ' ' && substr[start])
				start++;
			value_map->south_texture = ft_strdup(&substr[start]);
			while (substr[start] != ' ' && substr[start]
				!= '\t' && substr[start])
				start++;
			if (substr[start] == ' ' || substr[start] == '\t')
				value_map->south_texture = NULL;
		}
		else
			value_map->south_texture = NULL;
	}
	return (quantity_so);
}

int	get_path_north(char *line, t_value_from_map *value_map)
{
	char *substr;
	int start;
	static int quantity_no = 0;

	substr = ft_strnstr(line, "NO", ft_strlen(line));
	start = 0;
	if (NULL != substr && ft_strncmp(substr, "NO", 3))
	{
		quantity_no++;
		if (quantity_no == 1)
		{
			start = start + 2;
			while (substr[start] == ' ' && substr[start])
				start++;
			value_map->north_texture = ft_strdup(&substr[start]);
			while (substr[start] != ' ' && substr[start]
					!= '\t' && substr[start])
					start++;
				if (substr[start] == ' ' || substr[start] == '\t')
					value_map->north_texture = NULL;
		}
		else
			value_map->north_texture = NULL;
	}
	return (quantity_no);
}
#pragma endregion

#pragma region get_color_floor
int	take_number(char *substr, t_value_from_map *value_map,
	int quantity_number, int start)
{
	int number;
	int new_start;
	int count_comma;

	new_start = 0;
	count_comma = 0;
	number = ft_atoi(&substr[new_start]);
	if (quantity_number == 0)
		value_map->floor_color_r = number;
	else if (quantity_number == 1)
		value_map->floor_color_g = number;
	else if (quantity_number == 2)
		value_map->floor_color_b = number;
	new_start = new_start + len_number(number) - 1;
	if (number < 0)
		new_start++;
	new_start = new_start + pass_space(&substr[new_start]);
	while (substr[new_start] == ',')
	{
		new_start++;
		count_comma++;
	}
	if (count_comma > 1)
		value_map->floor_color_r = -1;
	return (new_start + start);
}

void	continue_get_val_color_floor(char *substr, t_value_from_map *value_map)
{
	int start;
	int quantity_number;
	int quantity_comma;

	start = 0;
	quantity_comma = 0;
	quantity_number = 0;
	while (substr[start])
	{
		start = start + pass_space(&substr[start]);
		while (substr[start] == '0')
			start++;
		start = take_number(&substr[start],
			value_map, quantity_number, start);
		if (substr[start] == ',' && quantity_number < 3)
			start++;
		else if ((substr[start] != ' ' && quantity_number > 2))
		{
			value_map->floor_color_r = -1;
			break ;
		}
		quantity_number++;
	}
}

int	get_value_color_floor(char *line, t_value_from_map *value_map)
{
	char		*substr;
	int			start;
	int			number;
	static int	quantity_f = 0;

	substr = ft_strnstr(line, "F", ft_strlen(line));
	start = 0;
	number = 0;
	if (NULL != substr && ft_strncmp(substr, "F", 2))
	{
		quantity_f++;
		if (count_comma(line) == 2)
		{
			if (quantity_f > 1)
				value_map->floor_color_r = -1;
			else if (quantity_f == 1)
			{
				start++;
				while (substr[start] == ' ' && substr[start])
					start++;
				continue_get_val_color_floor(&substr[start], value_map);
			}
		}
	}
	return (quantity_f);
}
#pragma endregion

#pragma region get_color
int	cont_get_val_color(char *substr, t_value_from_map *value_map,
	int quantity_number, int start)
{
	int number;
	int new_start;
	int count_comma;

	new_start = 0;
	count_comma = 0;
	number = ft_atoi(&substr[new_start]);
	if (quantity_number == 0)
		value_map->ceilling_color_r = number;
	else if (quantity_number == 1)
		value_map->ceilling_color_g = number;
	else if (quantity_number == 2)
		value_map->ceilling_color_b = number;
	new_start = new_start + len_number(number) - 1;
	new_start = new_start + pass_space(&substr[new_start]);
	while (substr[new_start] == ',')
	{
		new_start++;
		count_comma++;
	}
	if (count_comma > 1)
		value_map->ceilling_color_r = -1;
	return (new_start + start);
}

void	continue_get_val_color(char *substr, t_value_from_map *value_map)
{
	int start;
	int quantity_number;
	int quantity_comma;

	start = 0;
	quantity_comma = 0;
	quantity_number = 0;
	while (substr[start])
	{
		start = start + pass_space(&substr[start]);
		while (substr[start] == '0')
			start++;
		start = cont_get_val_color(&substr[start],
			value_map, quantity_number, start);
		if (substr[start] == ',' && quantity_number < 3)
			start++;
		else if ((substr[start] != ' ' && quantity_number > 2))
		{
			value_map->ceilling_color_r = -1;
			break ;
		}
		quantity_number++;
	}
}

int	get_value_color(char *line, t_value_from_map *value_map)
{
	char		*substr;
	int			start;
	int			number;
	static int	quantity_c = 0;

	substr = ft_strnstr(line, "C", ft_strlen(line));
	start = 0;
	number = 0;
	if (NULL != substr && ft_strncmp(substr, "C", 2))
	{
		quantity_c++;
		if (count_comma(line) == 2)
		{
			if (quantity_c > 1)
				value_map->ceilling_color_r = -1;
			else if (quantity_c == 1)
			{
				start++;
				while (substr[start] == ' ' && substr[start])
					start++;
				continue_get_val_color(&substr[start], value_map);
			}
		}
	}
	return (quantity_c);
}
#pragma endregion

#pragma region get_value_resolution

void	continue_get_value_resolution(char *substr, t_value_from_map *value_map)
{
	int start;
	int number;
	int quantity_number;

	start = 1;
	number = 0;
	quantity_number = 0;
	while (substr[start])
	{
		start = start + pass_space(&substr[start]);
		while (substr[start] == '0')
			start++;
		number = ft_atoi(&substr[start]);
		start = start + len_number(number) - 1;
		if (substr[start] != ' ' && substr[start] != '\t' &&
			!ft_isdigit(substr[start]) && substr[start] != '\0')
		{
			value_map->resolution_x = -1;
			break ;
		}
		if (quantity_number == 0)
			value_map->resolution_x = number;
		else if (quantity_number == 1)
			value_map->resolution_y = number;
		else
			value_map->resolution_x = -1;
		quantity_number++;
	}
}

int	get_value_resolution(char *line, t_value_from_map *value_map)
{
	char *substr;
	int start;
	int length_number;
	int number;
	static int quantity_r = 0;

	substr = ft_strnstr(line, "R", ft_strlen(line));
	start = 0;
	length_number = 0;
	number = 0;
	if (NULL != substr && ft_strncmp(substr, "R", 2))
	{
		quantity_r++;
		if (quantity_r > 1)
			value_map->resolution_x = -1;
		else if (quantity_r == 1)
			continue_get_value_resolution(&substr[start], value_map);
	}
	return (quantity_r);
}
#pragma endregion

int	string_from_space(char *line)
{
	int start;
	int len_str;
	int count_space;

	start = 0;
	count_space = 0;
	len_str = ft_strlen(line);
	while (line[start])
	{
		if (line[start] == ' ' || line[start] == '\t')
			count_space++;
		start++;
	}
	printf("str = %s|\n", &line[start]);
	if (count_space == len_str && /*(*/line[start] != '\0'/* || line[start + 1] == '\0')*/)
	{
		printf("HELL");
		return (1);
	}
	if ((line[start] == 'R')
		|| (line[start] == 'N' && line[start + 1] == 'O')
		|| (line[start] == 'S' && line[start + 1] == 'O')
		|| (line[start] == 'W' && line[start + 1] == 'E')
		|| (line[start] == 'E' && line[start + 1] == 'A')
		|| (line[start] == 'S') || (line[start] == 'C')
		|| (line[start] == 'F') || line[start] == '\0')
		return (0);
	return (1);
}

int		value_from_maps_not_null(t_value_from_map *value_map)
{
	if ((value_map->resolution_x >= 1 &&
		value_map->resolution_y >= 1) &&

		(value_map->north_texture != NULL &&
		value_map->south_texture != NULL &&
		value_map->west_texture != NULL &&
		value_map->east_texture != NULL &&
		value_map->sprite_texture != NULL) &&

		(value_map->floor_color_r >= 0 &&
		value_map->floor_color_g >= 0 &&
		value_map->floor_color_b >= 0) &&

		(value_map->ceilling_color_r >= 0 &&
		value_map->ceilling_color_g >= 0 &&
		value_map->ceilling_color_b >= 0))
		return (1);
	return (0);
}

void	manage_function(int fd, t_value_from_map *value_map)
{
	char *line;
	int threatment_line;

	threatment_line = 0;
	while (get_next_line(fd, &line))
	{
		ДОДЕЛАТЬ!!!
		if (string_from_space(line) == 1)
		{
			free(line);
			return ;
		}
		threatment_line += get_value_resolution(line, value_map);
		threatment_line += get_path_north(line, value_map);
		threatment_line += get_path_south(line, value_map);
		threatment_line += get_path_west(line, value_map);
		threatment_line += get_path_east(line, value_map);
		threatment_line += get_path_sprite(line, value_map);
		threatment_line += get_value_color(line, value_map);
		threatment_line += get_value_color_floor(line, value_map);
		// printf("value_from_maps_not_null: %d\n", value_from_maps_not_null(value_map));
		// printf("threatment_line: %d", threatment_line);
		if (threatment_line == 7 && value_from_maps_not_null(value_map))
		{
			printf("threatment_line: %d", threatment_line);
			printf("\nmap not valide\n");
		}
		free(line);
	}
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
}
