#include "../../cub3d.h"

// return an int **grid from the char **map
int	**get_grid_map(t_map *map)
{
	int	**grid;
	int	i;
	int	j;

	grid = malloc(sizeof(int *) * map->rows);
	if (!grid)
		return (NULL);
	i = -1;
	while (++i < map->rows)
	{
		grid[i] = malloc(sizeof(int) * ft_strlen(map->map[i]));
		if (!grid[i])
			return (NULL);
		j = -1;
		while (++j < ft_strlen(map->map[i]))
		{
			if (is_charset(map->map[i][j], "NSWE"))
				grid[i][j] = 0;
			else
				grid[i][j] = ft_atoi(map->map[i][j]);
		}
	}
	return (grid);
}

