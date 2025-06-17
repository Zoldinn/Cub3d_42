#include "../../cub3d.h"

/*
	if (keysym == KEY_W)
		y -= 0.1f;
	else if (keysym == KEY_S)
		y += 1;
	else if (keysym == KEY_A)
		x -= 0.1f;
	else if (keysym == KEY_D)
		x += 1; 
} */

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

