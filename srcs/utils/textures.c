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

t_texture	new_texture(t_game *game, char *path, int *a, int *b)
{
	t_texture	tex;

	tex.height = 0;
	tex.width = 0;
	tex.img = mlx_xpm_file_to_image(game->mlx, path, &tex.width, &tex.height);
	if (!tex.img)
	{
		printf("Texture not found.\n");
		end_game(game);
	}
	tex.addr = mlx_get_data_addr(tex.img,
		&tex.bpp, &tex.size_line, &tex.endian);
	return (tex);
}

void	init_texture(t_game *game)
{
	int	i;
	int	width;
	int	height;

	game->wall[WALL_N].img = NULL;
	game->wall[WALL_N] = new_texture(game, game->wall[0].path);
	game->wall[WALL_S].img = NULL;
	game->wall[WALL_S] = new_texture(game, game->wall[1].path);
	game->wall[WALL_W].img = NULL;
	game->wall[WALL_W] = new_texture(game, game->wall[2].path);
	game->wall[WALL_E].img = NULL;
	game->wall[WALL_E] = new_texture(game, game->wall[3].path);
	// game->wall[WALL_E] = new_texture(game, game->wall[3].path);
	i = -1;
	while (++i < 8)
		game->torch[i].img = NULL;
	height = 1000;
	width = 1000;
	game->torch[0] = new_texture(game, TORCH1_PATH, &width, &height);
	game->torch[1] = new_texture(game, TORCH2_PATH, &width, &height);
	game->torch[2] = new_texture(game, TORCH3_PATH, &width, &height);
	game->torch[3] = new_texture(game, TORCH4_PATH, &width, &height);
	game->torch[4] = new_texture(game, TORCH5_PATH, &width, &height);
	game->torch[5] = new_texture(game, TORCH6_PATH, &width, &height);
	game->torch[6] = new_texture(game, TORCH7_PATH, &width, &height);
	game->torch[7] = new_texture(game, TORCH8_PATH, &width, &height);
}
