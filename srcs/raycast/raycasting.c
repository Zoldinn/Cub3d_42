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
	camera->grid_pos[X] = (int) player->pos_x;
	camera->grid_pos[Y] = (int) player->pos_y;
	get_raydir_x(camera, &game->map, x);
	set_delta_dist(camera);
	set_step_and_sidedist(player, camera);
	while (game->map.map[camera->grid_pos[Y]][camera->grid_pos[X]] != '1')
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

// get the distance / length of the ray from player to the wall hit
void	get_raylength(t_camera *camera)
{
	if (camera->side_touch == 0)
		camera->raylength = camera->side_dist[X] - camera->delta_dist[X];
	else
		camera->raylength = camera->side_dist[Y] - camera->delta_dist[Y];
}

// set the height of the wall, the start/end drawing point
void	set_drawing(t_camera *camera)
{
	camera->line_height = (int) (HEIGHT / camera->raylength);
	camera->draw_start = (HEIGHT / 2) - (camera->line_height / 2);
	if (camera->draw_start < 0)
		camera->draw_start = 0;
	camera->draw_end = (HEIGHT / 2) + (camera->line_height / 2);
	if (camera->draw_end >= HEIGHT)
		camera->draw_end = HEIGHT - 1;
}

void	set_color(t_map *map, t_camera *camera)
{
	char	pos;

	pos = map->map[camera->grid_pos[Y]][camera->grid_pos[X]];
	if (pos == 1)
		camera->color = WALL_COLOR;
	else if (pos == 0)
		camera->color = FLOOR_COLOR;
	if (camera->side_touch == 1)
		camera->color /= 2;
}

void	do_all_rays(t_game *game, t_camera *camera)
{
	camera->x = -1;
	while (++camera->x < game->map.col_max)
	{
		dda_algo(game, camera, &game->player, camera->x);
		get_raylength(camera);
		set_drawing(camera);
		draw_verline(&game->screen_img, camera);
	}
}
