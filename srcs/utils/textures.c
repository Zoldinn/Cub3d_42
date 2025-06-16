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
