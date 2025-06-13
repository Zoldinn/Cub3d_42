#include "../../cub3d.h"

void	render_map(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->window,
			game->txt[WALL].img, 0, HEIGHT / 2);
	mlx_put_image_to_window(game->mlx, game->window,
			game->txt[FLOOR].img, HEIGHT / 2, HEIGHT);
}
