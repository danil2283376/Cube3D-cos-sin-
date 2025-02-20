/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_sprite.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:06:24 by scolen            #+#    #+#             */
/*   Updated: 2020/12/20 13:21:20 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_mms/mlx.h"
#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include "../cube3D.h"

void	get_path_sprite(char *line, t_value_from_map *value_map)
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
			value_map->sprite_texture = ft_strdup(&substr[start]); // MALLOC!
			while (substr[start] != ' ' && substr[start]
				!= '\t' && substr[start])
				start++;
			if (substr[start] == ' ' || substr[start] == '\t')
				value_map->sprite_texture = NULL;
		}
		else if (quantity_s > 2)
			value_map->sprite_texture = NULL;
	}
	// return (quantity_s);
}
