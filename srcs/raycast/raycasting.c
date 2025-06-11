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

// the DDA algorithm which should return the distance to a wall
int	dda_algo(t_game *game, t_camera *camera, t_player *player)
{
	camera->grid = get_grid_map(game);
	if (!camera->grid)
		return (1);
	camera->grid_pos[X] = (int) player->pos_x;
	camera->grid_pos[Y] = (int) player->pos_y;
	set_delta_dist(camera);
	set_step_and_sidedist(player, camera);
	while (camera->grid[camera->grid_pos[X]][camera->grid_pos[Y]] != 1)
	{
		if (camera->side_dist[X] < camera->side_dist[Y])
		{
			camera->side_dist[X] += camera->delta_dist[X];
			camera->grid_pos[X] += camera->step[X];
			camera->side_touch = 0;
		}
		else
		{
			camera->side_dist[Y] += camera->delta_dist[Y];
			camera->grid_pos[Y] += camera->step[Y];
			camera->side_touch = 1;
		}
	}
}
