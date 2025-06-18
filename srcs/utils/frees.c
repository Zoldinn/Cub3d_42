#include "../../cub3d.h"

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
	if (map->rgb)
		free_arr(map->rgb);
	if (map->txt)
		free_txt(map->txt);
}

void	free_walls_texture(t_game *game)
{
	if (game->wall[0].path)
		free(game->wall[0].path);
	if (game->wall[1].path)
		free(game->wall[1].path);
	if (game->wall[2].path)
		free(game->wall[2].path);
	if (game->wall[3].path)
		free(game->wall[3].path);
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
