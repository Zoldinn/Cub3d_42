#include "../../cub3d.h"

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


// the DDA algorithm which should return the distance to a wall
int	dda_algo(t_map *map)
{
	int	**grid;

	grid = get_grid_map(map);
	if (!grid)
		return ;
	
}