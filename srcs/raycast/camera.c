#include "../../cub3d.h"

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

// North and south are reversed (because axe Y is reversed)
void	init_camera_angle(t_camera *camera, t_map *map)
{
	char		player;

	player = get_initial_dir(map);
	if (player == 'N')
		camera->angle_rad = (3 * PI) / 2;
	else if (player == 'S')
		camera->angle_rad = PI / 2;
	else if (player == 'W')
		camera->angle_rad = PI;
	else if (player == 'E')
		camera->angle_rad = 0;
}

void	update_camera_dir(t_camera *camera)
{
	camera->dir[X] = cos(camera->angle_rad);
	camera->dir[Y] = sin(camera->angle_rad);
	camera->plane[X] = -camera->dir[Y] * tan(FOV_DEGREE / 2);
	camera->angle_rad = camera->dir[X] * tan(FOV_DEGREE / 2);
}
