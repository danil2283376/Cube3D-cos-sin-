/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_south.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:12:01 by scolen            #+#    #+#             */
/*   Updated: 2020/12/20 13:20:51 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_mms/mlx.h"
#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include "../cube3D.h"

void	get_path_south(char *line, t_value_from_map *value_map)
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
			value_map->south_texture = ft_strdup(&substr[start]); // MALLOC!
			while (substr[start] != ' ' && substr[start]
				!= '\t' && substr[start])
				start++;
			if (substr[start] == ' ' || substr[start] == '\t')
				value_map->south_texture = NULL;
		}
		else
			value_map->south_texture = NULL;
	}
	// return (quantity_so);
}
