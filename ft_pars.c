/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:15:09 by scolen            #+#    #+#             */
/*   Updated: 2020/12/17 21:46:16 by scolen           ###   ########.fr       */
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

#pragma region path_prite
void	get_path_sprite(char *line, t_value_from_map *value_map)
{
	char *substr;
	int start;

	substr = ft_strnstr(line, "S", ft_strlen(line));
	start = 0;
	if (NULL != substr && ft_strncmp(substr, "S", 2))
	{
		start = start + 2;
		while (substr[start] == ' ' && substr[start])
			start++;
		value_map->sprite_texture = ft_strdup(&substr[start]);
	}
}

void	get_path_east(char *line, t_value_from_map *value_map)
{
	char *substr;
	int start;

	substr = ft_strnstr(line, "EA", ft_strlen(line));
	start = 0;
	if (NULL != substr && ft_strncmp(substr, "EA", 3))
	{
		start = start + 2;
		while (substr[start] == ' ' && substr[start])
			start++;
		value_map->east_texture = ft_strdup(&substr[start]);
	}
}

void	get_path_west(char *line, t_value_from_map *value_map)
{
	char *substr;
	int start;

	substr = ft_strnstr(line, "WE", ft_strlen(line));
	start = 0;
	if (NULL != substr && ft_strncmp(substr, "WE", 3))
	{
		start = start + 2;
		while (substr[start] == ' ' && substr[start])
			start++;
		value_map->west_texture = ft_strdup(&substr[start]);
	}
}

void	get_path_south(char *line, t_value_from_map *value_map)
{
	char *substr;
	int start;

	substr = ft_strnstr(line, "SO", ft_strlen(line));
	start = 0;
	if (NULL != substr && ft_strncmp(substr, "SO", 3))
	{
		start = start + 2;
		while (substr[start] == ' ' && substr[start])
			start++;
		value_map->south_texture = ft_strdup(&substr[start]);
	}
}

void	get_path_north(char *line, t_value_from_map *value_map)
{
	char *substr;
	int start;

	substr = ft_strnstr(line, "NO", ft_strlen(line));
	start = 0;
	if (NULL != substr && ft_strncmp(substr, "NO", 3))
	{
		start = start + 2;
		while (substr[start] == ' ' && substr[start])
			start++;
		value_map->north_texture = ft_strdup(&substr[start]);
	}
}
#pragma endregion

void	get_value_color_floor(char *line, t_value_from_map *value_map)
{
	char *substr;
	int start;
	int length_number;
	(void)value_map;
	int number;

	substr = ft_strnstr(line, "F", ft_strlen(line));
	start  = 0;
	length_number = 0;
	number = 0;
	if (NULL != substr && ft_strncmp(substr, "F", 2))
	{
		start++;
		while (substr[start] == ' ' && substr[start])
			start++;

		// printf("\nFloor: %s\n", &substr[start]);
	}
}

void	get_value_resolution(char *line, t_value_from_map *value_map)
{
	char *substr;
	int start;
	int length_number;
	int number;

	substr = ft_strnstr(line, "R", ft_strlen(line));
	start = 0;
	length_number = 0;
	number = 0;
	if (NULL != substr && ft_strncmp(substr, "R", 2))
	{
		start++;
		while (substr[start] == ' ' && substr[start + 1] != '\0')
			start++;
		number = ft_atoi(&substr[start]);
		value_map->resolution_x = number;
		length_number = len_number(number);
		if (number < 0)
			length_number++;
		start = start + length_number;
		number = ft_atoi(&substr[start]);
		value_map->resolution_y = number;
	}
}

void	manage_function(int fd, t_value_from_map *value_map)
{
	char *line;
	while (get_next_line(fd, &line))
	{
		get_value_resolution(line, value_map);
		get_path_north(line, value_map);
		get_path_south(line, value_map);
		get_path_west(line, value_map);
		get_path_east(line, value_map);
		get_path_sprite(line, value_map);
		get_value_color_floor(line, value_map);
		free(line);
	}
	printf("Resolution: x = %d, y = %d\n", value_map->resolution_x, value_map->resolution_y);
	printf("North = %s\n", value_map->north_texture);
	printf("South = %s\n", value_map->south_texture);
	printf("West = %s\n", value_map->west_texture);
	printf("East = %s\n", value_map->east_texture);
	printf("Sprite = %s\n", value_map->sprite_texture);
}
