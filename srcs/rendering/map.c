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
	game->wall.img = NULL;
	game->floor.img = NULL;
	game->empty.img = NULL;
	game->player.texture.img = NULL;
	game->oob.img = NULL;
	game->wall = new_texture(game, WALL_PATH);
	game->floor = new_texture(game, FLOOR_PATH);
	game->empty = new_texture(game, EMPTY_PATH);
	game->player.texture = new_texture(game, PLAYER_PATH);
	game->oob = new_texture(game, OOB_PATH);
}

void	fill_map(t_game *game, int x, int y)
{
	char	pos;

	if (y < (int)ft_strlen(game->map.map[x]))
	{
		pos = game->map.map[x][y];
		if (pos == '1')
			mlx_put_image_to_window(game->mlx, game->window, game->wall.img,
				SIZE * y, SIZE * x);
		if (pos == '0' || (pos == 'N' || pos == 'S' || pos == 'W'
			|| pos == 'E'))
			mlx_put_image_to_window(game->mlx, game->window, game->floor.img,
				SIZE * y, SIZE * x);
		if (pos == ' ')
			mlx_put_image_to_window(game->mlx, game->window, game->empty.img,
				SIZE * y, SIZE * x);
		if ((pos == 'N' || pos == 'S' || pos == 'W' || pos == 'E')
			&& (game->player.pos_x == -1 && game->player.pos_x == -1))
		{
			game->player.pos_x = x;
			game->player.pos_y = y;
		}
	}
	else
		mlx_put_image_to_window(game->mlx, game->window, game->oob.img,
			SIZE * y, SIZE * x);
}
