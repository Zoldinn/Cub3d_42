#include "../../cub3d.h"

void	ray_draw(t_game *game)
{
	double	x;
	double	y;

	x = game->player.pos_x + 0.5f;
	y = game->player.pos_y;
	while (game->map.map[(int)y][(int)x] != '1')
	{
		y *= SIZE;
		mlx_pixel_put(game->mlx, game->window, x * SIZE,
			y, PLAYER_COLOR);
		y--;
		y /= SIZE;
	}
}
