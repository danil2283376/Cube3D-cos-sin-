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

t_list	*add_map(t_list **map)
{
	char *line;
	int fd;

	fd = open("map.cub", O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		ft_lstadd_back(map, ft_lstnew(line));
		// free(line);
	}
	return (&(**map));
}

// int main()
// {
// 	// int x = 30;
// 	// int y = 30;
// 	void *mlx = NULL;
// 	void *window = NULL;
// 	int len_strng;
// 	int count_len;
// 	t_list *list_map;
// 	int start;
// 	int start_string;
// 	char *string;
// 	t_min_max_value min_max_value;

// 	start = 0;
// 	min_max_value.x_min = 30;
// 	start_string = 0;
// 	list_map = add_map(&list_map);
// 	// while (list_map)
// 	// {
// 	// 	printf("%s\n", list_map->content);
// 	// 	list_map = list_map->next;
// 	// }
// 	count_len = ft_lstsize(list_map);
// 	// printf("\ncount_len: %d\n", count_len);
// 	mlx = mlx_init();
// 	window = mlx_new_window(mlx, 640, 480, "Cube3D");
// 	while (start < count_len && list_map)
// 	{
// 		// (char *)list_map->content[start_string]
// 		string = (char *)list_map->content;
// 		while (string[start_string] == '1')
// 		{
// 			printf("%d\n", 1);
// 			while (y++ < 50)
// 			{
// 				x = 30;
// 				while (x++ < 50)
// 				{
// 					mlx_pixel_put(mlx, window, x, y, 0xFFFFFF);
// 				}
// 			}
// 			y = 30;
// 			start_string++;
// 		}
// 		start_string = 0;
// 		list_map = list_map->next;
// 		start++;
// 	}
// 	printf("END\n");
// 	mlx_loop(mlx);
// 	return (0);
// }
