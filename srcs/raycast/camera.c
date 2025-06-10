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

int	*get_raydir_x(t_camera *camera, t_map *map, int x)
{
	int		*raydirs;
	double	camera_x;

	raydirs = malloc(sizeof(int) * 2);
	if (!raydirs)
		return (NULL);
	camera_x = 2 * x / (double) map->col_max - 1;
	raydirs[X] = camera->dir[X] + camera->plane[X] * camera_x;
	raydirs[Y] = camera->dir[Y] + camera->plane[Y] * camera_x;
	return (raydirs);
}

// length from x/y to x/y side
void	set_delta_dist(t_camera *camera)
{
	if (camera->ray_dir[X] == 0)
		camera->delta_dist[X] = 1e30;
	else
		camera->delta_dist[X] = fabs(1.0 / camera->ray_dir[X]);
	if (camera->ray_dir[Y] == 0)
		camera->delta_dist[Y] = 1e30;
	else
		camera->delta_dist[Y] = fabs(1.0 / camera->ray_dir[Y]);
}

void	set_step_and_sidedist(t_player *player, t_camera *camera)
{
	double	dist_to_grid;

	camera->step[X] = 1;
	dist_to_grid = camera->grid_pos[X] + 1 - player->pos_x;
	camera->side_dist[X] = (dist_to_grid) * camera->delta_dist[X];
	if (camera->ray_dir[X] < 0)
	{
		camera->step[X] = -1;
		dist_to_grid = player->pos_x - camera->grid_pos[X];
		camera->side_dist[X] = (dist_to_grid) * camera->delta_dist[X];
	}
	camera->step[Y] = 1;
	dist_to_grid = camera->grid_pos[Y] + 1 - player->pos_y;
	camera->side_dist[Y] = (dist_to_grid) * camera->delta_dist[Y];
	if (camera->ray_dir[Y] < 0)
	{
		camera->step[Y] = -1;
		dist_to_grid = player->pos_y - camera->grid_pos[Y];
		camera->side_dist[Y] = (dist_to_grid) * camera->delta_dist[Y];
	}
}
