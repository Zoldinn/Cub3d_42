#include "../../cub3d.h"

void	get_textures_wall(t_game *game)
{
	char	**arr;
	int		i;

	i = 0;
	while (i < 4)
	{
		arr = ft_split(game->map.txt[i], " \t");
		game->wall[i].path = ft_strdup(arr[1]);
		free_arr(arr);
		i++;
	}
}

t_texture	new_texture(t_game *game, char *path)
{
	t_texture	tex;

	tex.img = mlx_xpm_file_to_image(game->mlx, path, &tex.width, &tex.height);
	if (!tex.img)
	{
		printf("Texture not found.\n");
		end_game(game);
	}
	return (tex);
}

void	init_texture(t_game *game)
{
	game->wall[WALL_N].img = NULL;
	// game->wall[WALL_N] = new_texture(game, game->wall[0].path);
	game->wall[WALL_S].img = NULL;
	// game->wall[WALL_S] = new_texture(game, game->wall[1].path);
	game->wall[WALL_W].img = NULL;
	// game->wall[WALL_W] = new_texture(game, game->wall[2].path);
	game->wall[WALL_E].img = NULL;
	// game->wall[WALL_E] = new_texture(game, game->wall[3].path);
}
