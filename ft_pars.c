/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:15:09 by scolen            #+#    #+#             */
/*   Updated: 2020/12/15 19:56:43 by scolen           ###   ########.fr       */
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
	while (number > 0)
	{
		number = number / 10;
		len++;
	}
	return (len);
}

void	continue_get_value_resulution(char *s, t_value_from_map *value_from_map)
{
	(void)s;
	(void)value_from_map;

	// printf("value_from_map: %d\n", value_from_map->resolution_x);
	value_from_map->resolution_y = ft_atoi(&s[0]);
	printf("%d, %d", value_from_map->resolution_x, value_from_map->resolution_y);
}

void	get_value_resolution(int fd, t_value_from_map *value_from_map)
{
	char *line;
	int start;
	// (void)value_from_map;
	int number;
	start = 0;
	while (get_next_line(fd, &line) == 1)
	{
		while (line[start] != 'R' && line[start])
		{
			start++;
			// break ;
		}
		if (line[start] == 'R')
			break ;
		free(line);
	}
	// printf("%d", start);
	while (line[start + 1] == ' ' || line[start] == ' ')
		start++;
	number = ft_atoi(&line[start]);
	value_from_map->resolution_x = number;
	start = start + len_number(number);
	// printf("string: %s\n", &line[start]);
	continue_get_value_resulution(&line[start], value_from_map);
}

void	manage_function(int fd, t_value_from_map *value_map)
{
	get_value_resolution(fd, value_map);
}
