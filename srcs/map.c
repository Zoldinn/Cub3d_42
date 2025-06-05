#include "../cub3d.h"

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
			mlx_put_image_to_window(game->mlx, game->window,
				game->txt[WALL].img, SIZE * y, SIZE * x);
		else if (pos == '0')
			mlx_put_image_to_window(game->mlx, game->window,
				game->txt[FLOOR].img, SIZE * y, SIZE * x);
		else if (pos == ' ')
			mlx_put_image_to_window(game->mlx, game->window,
				game->txt[EMPTY].img, SIZE * y, SIZE * x);
		else if (pos == 'N' || pos == 'S' || pos == 'W' || pos == 'E')
		{
			game->player.pos_x = x;
			game->player.pos_y = y;
		}
	}
	else
		mlx_put_image_to_window(game->mlx, game->window, game->txt[OOB].img,
			SIZE * y, SIZE * x);
}

//render the map to print it in 2D
int	render_map(t_game *game)
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
	mlx_put_image_to_window(game->mlx, game->window,
		game->player.texture.img, SIZE * game->player.pos_y,
		SIZE * game->player.pos_x);
	return (0);
}
