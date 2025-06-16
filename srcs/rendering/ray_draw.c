#include "../../cub3d.h"

void	draw_ray(t_game *game, int color)
{
	double		camera_x;
	double		ray_dir[2];
	double		ray[2];
	t_camera	*camera;
	int			x;

	camera = &game->player.camera;
	x = 0;
	while (x < game->map.col_max)
	{
		camera_x = 2 * x / (double) game->map.col_max - 1;
		ray_dir[X] = camera->dir[X] + camera->plane[X] * camera_x;
		ray_dir[Y] = camera->dir[Y] + camera->plane[Y] * camera_x;
		ray[X] = game->player.pos_x;
		ray[Y] = game->player.pos_y;
		while (game->map.map[(int)ray[Y]][(int)ray[X]] != '1')
		{
			put_pixel(&game->map2d_img, ray[X] * SIZE + SIZE / 2,
				ray[Y] * SIZE + SIZE / 2, color);
			/* mlx_pixel_put(game->mlx, game->window,
				ray[X] * SIZE + SIZE / 2,
				ray[Y] * SIZE + SIZE / 2, color); */
			ray[Y] += ray_dir[Y] * 0.1;
			ray[X] += ray_dir[X] * 0.1;
		}
		x += 1;
	}
}

