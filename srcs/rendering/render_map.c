#include "../../cub3d.h"

//draw a square in pixels
void	draw_square(t_game *game, int color)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = game->player.pos_x * SIZE;
	y = game->player.pos_y * SIZE;
	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			mlx_pixel_put(game->mlx, game->window, y + j,
				x + i, color);
			j++;
		}
		i++;
	}
}

//update the map by adding layers of images/pixels
void	update_map2D(t_game *game)
{
	double	x;
	double	y;

	if (game->player.neg_dir == 0)
	{
		x = ceil(game->player.pos_x);
		y = ceil(game->player.pos_y);
	}
	else
	{
		x = floor(game->player.pos_x);
		y = floor(game->player.pos_y);
	}
	if (game->map.map[(int)x][(int)y]
		&& game->map.map[(int)x][(int)y] == '1')
		draw_square(game, WALL_COLOR);
	else
		draw_square(game, FLOOR_COLOR);
}

//render the map to print it in 2D
int	render_map2D(t_game *game)
{
	int	x;
	int	y;
	
	x = 0;
	while (x < game->map.rows)
	{
		y = 0;
		while (y <= game->map.col_max)
		{
			fill_map(game, x, y);
			y++;
		}
		x++;
	}
	draw_square(game, PLAYER_COLOR);
	return (0);
}
