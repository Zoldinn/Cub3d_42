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

double	get_rad(double degree)
{
	return ((degree * PI) / 180);
}