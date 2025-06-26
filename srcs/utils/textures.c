#include "../../cub3d.h"

void	get_textures_wall(t_game *game)
{
	char	**arr;
	int		i;

	i = 0;
	while (i < 4)
	{
		game->wall[i].path = NULL;
		arr = ft_split(game->map.txt[i], " \t");
		game->wall[i].path = ft_strdup(arr[1]);
		free_arr(arr);
		i++;
	}
}

t_texture	new_texture(t_game *game, char *path)
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

void	init_torch(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		game->torch[i].img = NULL;
		game->torch[i].width = 60;
		game->torch[i].height = 60;
	}
	game->torch[0] = new_texture(game, TORCH1_PATH);
	game->torch[1] = new_texture(game, TORCH2_PATH);
	game->torch[2] = new_texture(game, TORCH3_PATH);
	game->torch[3] = new_texture(game, TORCH4_PATH);
	game->torch[4] = new_texture(game, TORCH5_PATH);
	game->torch[5] = new_texture(game, TORCH6_PATH);
	game->torch[6] = new_texture(game, TORCH7_PATH);
	game->torch[7] = new_texture(game, TORCH8_PATH);
}

void	init_texture(t_game *game)
{
	char	*path_temp;
	int		i;

	i = 0;
	while (i < 4)
	{
		path_temp = ft_strdup(game->wall[i].path);
		free(game->wall[i].path);
		game->wall[i].img = NULL;
		game->wall[i] = new_texture(game, path_temp);
		free(path_temp);
		i++;
	}
	init_torch(game);
}
