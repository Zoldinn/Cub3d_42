#include "../../cub3d.h"

void	draw_ray(t_game *game, t_player *player, t_camera *camera, int color)
{
	double	pos_screen[2];

	pos_screen[X] = player->pos_x * SIZE + (SIZE / 2);
	pos_screen[Y] = player->pos_y * SIZE + (SIZE / 2);
	while (game->map.map[(int)(pos_screen[Y] / SIZE)]
		[(int)(pos_screen[X] / SIZE)] != '1')
	{
		mlx_pixel_put(game->mlx, game->window, pos_screen[X], pos_screen[Y],
			color);
		pos_screen[Y] += camera->dir[Y];
		pos_screen[X] += camera->dir[X];
	}
}

