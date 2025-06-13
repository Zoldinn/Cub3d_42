#include "../../cub3d.h"

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

// Step is the direction in which the ray move.
// SideDist is the dist from player to the first side of the grid in x and y
// like the player is in x0.6 y0.7 so side_dist[x] = 0.4 and y = 0.3
void	set_step_and_sidedist(t_player *player, t_camera *camera)
{
	double	dist_to_grid;

	camera->step[X] = 1;
	dist_to_grid = player->grid_pos[X] + 1 - player->pos_x;
	camera->side_dist[X] = (dist_to_grid) * camera->delta_dist[X];
	if (camera->ray_dir[X] < 0)
	{
		camera->step[X] = -1;
		dist_to_grid = player->pos_x - player->grid_pos[X];
		camera->side_dist[X] = (dist_to_grid) * camera->delta_dist[X];
	}
	camera->step[Y] = 1;
	dist_to_grid = player->grid_pos[Y] + 1 - player->pos_y;
	camera->side_dist[Y] = (dist_to_grid) * camera->delta_dist[Y];
	if (camera->ray_dir[Y] < 0)
	{
		camera->step[Y] = -1;
		dist_to_grid = player->pos_y - player->grid_pos[Y];
		camera->side_dist[Y] = (dist_to_grid) * camera->delta_dist[Y];
	}
}

void	get_raydir_x(t_camera *camera, t_map *map, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double) map->col_max - 1;
	camera->ray_dir[X] = camera->dir[X] + camera->plane[X] * camera_x;
	camera->ray_dir[Y] = camera->dir[Y] + camera->plane[Y] * camera_x;
}

// The DDA algorithm
void	dda_algo(t_game *game, t_camera *camera, t_player *player, int x)
{
	player->grid_pos[X] = (int) player->pos_x;
	player->grid_pos[Y] = (int) player->pos_y;
	get_raydir_x(camera, &game->map, x);
	set_delta_dist(camera);
	set_step_and_sidedist(player, camera);
	while (game->map.map[player->grid_pos[Y]][player->grid_pos[X]] != '1')
	{
		if (camera->side_dist[X] < camera->side_dist[Y])
		{
			camera->side_dist[X] += camera->delta_dist[X];
			player->grid_pos[X] += camera->step[X];
			camera->side_touch = 0;
		}
		else
		{
			camera->side_dist[Y] += camera->delta_dist[Y];
			player->grid_pos[Y] += camera->step[Y];
			camera->side_touch = 1;
		}
	}
}

void	do_all_rays(t_game *game)
{
	int	x;

	x = -1;
	while (++x < game->map.col_max)
	{
		dda_algo(game, &game->player.camera, &game->player, x);
	}
}

// get the distance / length of the ray from player to the wall hit
/* void	get_raylength(t_camera *camera)
{
	if (camera->side_touch == 0)
		camera->raylength = camera->side_dist[X] - camera->delta_dist[X];
	else
		camera->raylength = camera->side_dist[Y] - camera->delta_dist[Y];
} */



