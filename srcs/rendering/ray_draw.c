#include "../../cub3d.h"

void	ray_draw(t_game *game)
{
	double	x;
	double	y;

	x = game->player.pos_x;
	y = game->player.pos_y + 0.5f;
	while (game->map.map[(int)x][(int)y] != '1')
	{
		x *= SIZE;
		mlx_pixel_put(game->mlx, game->window, y * SIZE,
			x, PLAYER_COLOR);
		x--;
		x /= SIZE;
	}
}
