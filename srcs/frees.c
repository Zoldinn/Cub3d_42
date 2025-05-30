#include "../cub3d.h"

void	free_txt(char **arr)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_map(t_map *map)
{
	if (map->data)
		free_arr(map->data);
	if (map->map)
		free_arr(map->map);
	if (map->txt)
		free_txt(map->txt);
}

void	free_and_exit(t_map *map, int code)
{
	free_map(map);
	exit(code);
}

void	free_arr(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (i < arrlen(arr))
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}
