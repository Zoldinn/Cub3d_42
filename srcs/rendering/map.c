#include "../../cub3d.h"

t_texture	new_texture(t_game *game, char *path)
{
	t_texture	texture;
	int			x;
	int			y;

	x = SIZE;
	y = SIZE;
	texture.img = mlx_xpm_file_to_image(game->mlx, path, &x, &y);
	if (!texture.img)
	{
		printf("Texture not found.\n");
		end_game(game);
	}
	return (texture);
}

void	init_texture(t_game *game)
{
	game->txt[WALL].img = NULL;
	game->txt[FLOOR].img = NULL;
	game->txt[EMPTY].img = NULL;
	game->player.texture.img = NULL;
	game->txt[OOB].img = NULL;
	game->txt[WALL] = new_texture(game, WALL_PATH);
	game->txt[FLOOR] = new_texture(game, FLOOR_PATH);
	game->txt[EMPTY] = new_texture(game, EMPTY_PATH);
	game->player.texture = new_texture(game, PLAYER_PATH);
	game->txt[OOB] = new_texture(game, OOB_PATH);
}

void	fill_map(t_game *game, int x, int y)
{
	char	pos;

	if (y < (int)ft_strlen(game->map.map[x]))
	{
		pos = game->map.map[x][y];
		if (pos == '1')
			draw_square(&game->map2d_img, x, y, WALL_COLOR);
		if (pos == '0' || (pos == 'N' || pos == 'S' || pos == 'W'
				|| pos == 'E'))
			draw_square(&game->map2d_img, x, y, FLOOR_COLOR);
		if (pos == ' ')
			draw_square(&game->map2d_img, x, y, EMPTY_COLOR);
		if ((pos == 'N' || pos == 'S' || pos == 'W' || pos == 'E')
			&& (game->player.pos_x == -1 && game->player.pos_x == -1))
		{
			game->player.pos_x = y;
			game->player.pos_y = x;
		}
	}
	else
		draw_square(&game->map2d_img, x, y, OOB_COLOR);
}
