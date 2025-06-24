#include "../../cub3d.h"

//fill the 2d map with pixels
void	fill_map(t_game *game, int x, int y)
{
	char	pos;

	if (y < (int)ft_strlen(game->map.map[x]))
	{
		pos = game->map.map[x][y];
		if (pos == '1')
			draw_square(&game->screen_img, x, y, WALL_COLOR);
		if (pos == '0' || (pos == 'N' || pos == 'S' || pos == 'W'
				|| pos == 'E'))
			draw_square(&game->screen_img, x, y, FLOOR_COLOR);
		if (pos == ' ')
			draw_square(&game->screen_img, x, y, EMPTY_COLOR);
		if (pos == 'D')
			draw_square(&game->screen_img, x, y, DOOR_COLOR);
	}
	else
		draw_square(&game->screen_img, x, y, OOB_COLOR);
}

//render the 2d img of the map
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
	draw_player(&game->screen_img, game->player.pos_y, game->player.pos_x,
		PLAYER_COLOR);
	return (0);
}
