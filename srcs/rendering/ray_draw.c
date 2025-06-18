#include "../../cub3d.h"

void	draw_verline(t_my_img *img, t_camera *camera)
{
	int	y;

	y = camera->draw_start;
	while (y <= camera->draw_end)
	{
		camera->color = WALL_COLOR;
		if (camera->side_touch == 1)
			camera->color /= 2;
		put_pixel(img, camera->x, y, camera->color);
		y++;
	}
}

//draw a cone of pixels in order to see raycasting
void	draw_ray(t_game *game, int color)
{
	double		camera_x;
	double		ray_dir[2];
	double		ray[2];
	t_camera	*camera;
	int			x;

	camera = &game->player.camera;
	x = -1;
	while (++x < WIDTH)
	{
		camera_x = 2 * x / (double) game->map.col_max - 1;
		ray_dir[X] = camera->dir[X] + camera->plane[X] * camera_x;
		ray_dir[Y] = camera->dir[Y] + camera->plane[Y] * camera_x;
		ray[X] = game->player.pos_x;
		ray[Y] = game->player.pos_y;
		while (game->map.map[(int)ray[Y]][(int)ray[X]] != '1')
		{
			put_pixel(&game->screen_img, ray[X] * SIZE,
				ray[Y] * SIZE, color);
			ray[Y] += ray_dir[Y] * 0.01;
			ray[X] += ray_dir[X] * 0.01;
		}
	}
}

