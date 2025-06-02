#include "../cub3d.h"

t_texture	new_texture(t_game *game, char *path)
{
	t_texture	texture;
	int			x;
	int			y;

	x = 64;
	y = 64;
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
	game->wall = new_texture(game, WALL_PATH);
	game->floor = new_texture(game, FLOOR_PATH);
}

void	fill_map(t_game *game, int x, int y)
{
	char	pos;

	pos = game->map.map[x][y];
	if (pos == '1')
		mlx_put_image_to_window(game->mlx, game->window, game->wall.img,
			64 * y, 64 * x);
	else if (pos == '0')
		mlx_put_image_to_window(game->mlx, game->window, game->floor.img,
			64 * y, 64 * x);
}

int	render_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map.rows)
	{
		y = 0;
		while (game->map.map[x][y] || y < game->map.col_max)
		{
			fill_map(game, x, y);
			y++;
		}
		x++;
	}
	return (0);
}
