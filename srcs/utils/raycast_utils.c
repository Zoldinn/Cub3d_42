#include "../cub3d.h"

char	get_player_init_dir(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < ft_strlen(map->map[i]))
		{
			if (is_charset(map->map[i][j], "NSWE"))
				return (map->map[i][j]);
		}
	}
	return (0);
}

// return an int **grid from the char **map
int	**get_grid_map(t_game *game)
{
	int	**grid;
	int	i;
	int	j;

	grid = malloc(sizeof(int *) * game->map.rows);
	if (!grid)
		return (NULL);
	i = -1;
	while (++i < game->map.rows)
	{
		grid[i] = malloc(sizeof(int) * ft_strlen(game->map.map[i]));
		if (!grid[i])
			return (NULL);
		j = -1;
		while (++j < ft_strlen(game->map.map[i]))
		{
			if (is_charset(game->map.map[i][j], "NSWE"))
				grid[i][j] = 0;
			else
				grid[i][j] = ft_atoi(game->map.map[i][j]);
		}
	}
	return (grid);
}
