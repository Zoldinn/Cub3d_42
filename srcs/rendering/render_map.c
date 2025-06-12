#include "../../cub3d.h"

//draw a square (the player) in pixels
void	draw_player(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			mlx_pixel_put(game->mlx, game->window, x + i,
				y + j, color);
			j++;
		}
		i++;
	}
}

//draw a line of pixel horizontaly behind the player
void	draw_line_horizontal(t_game *game, double x, double y, int limit)
{
	int	i;
	int	j;
	int	a;
	int	b;

	i = 0;
	while (i < SIZE)
	{
		j = -4;
		while (j < limit)
		{
			a = floor((y + j) / SIZE);
			b = floor((x + i) / SIZE);
			if (game->map.map[a][b] == '1')
				mlx_pixel_put(game->mlx, game->window, x + i,
					y + j, WALL_COLOR);
			else
				mlx_pixel_put(game->mlx, game->window, x + i,
					y + j, FLOOR_COLOR);
			j++;
		}
		i++;
	}
}

//draw a line of pixel verticaly behind the player
void	draw_line_vertical(t_game *game, double x, double y, int limit)
{
	int	i;
	int	j;
	int	a;
	int	b;

	i = 0;
	while (i < SIZE)
	{
		j = -4;
		while (j < limit)
		{
			a = floor((y + i) / SIZE);
			b = floor((x + j) / SIZE);
			if (game->map.map[a][b] == '1')
				mlx_pixel_put(game->mlx, game->window, x + j,
					y + i, WALL_COLOR);
			else
				mlx_pixel_put(game->mlx, game->window, x + j,
					y + i, FLOOR_COLOR);
			j++;
		}
		i++;
	}
}

//update the map by adding lines of pixels behind the player
void	update_map2d(t_game *game)
{
	double	x;
	double	y;

	x = game->player.pos_x;
	y = game->player.pos_y;
	if (game->player.go_up == 1)
	{
		y += 1;
		draw_line_horizontal(game, x * SIZE, y * SIZE, 2);
	}
	else if (game->player.go_down == 1)
	{
		draw_line_horizontal(game, x * SIZE, y * SIZE, 3);
	}
	else if (game->player.go_left == 1)
	{
		x += 1;
		draw_line_vertical(game, x * SIZE, y * SIZE, 2);
	}
	else if (game->player.go_right == 1)
	{
		draw_line_vertical(game, x * SIZE, y * SIZE, 3);
	}
}

//render the map to print it in 2D
int	render_map2d(t_game *game)
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
	draw_player(game, game->player.pos_x * SIZE, game->player.pos_y * SIZE,
		PLAYER_COLOR);
	return (0);
}
