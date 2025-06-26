#include "../../cub3d.h"

void	init_map(t_map *map)
{
	map->data = NULL;
	map->map = NULL;
	map->rgb = NULL;
	map->txt = NULL;
	map->door_pos_x = NULL;
	map->door_pos_y = NULL;
	map->rows = 0;
	map->col_max = 0;
	map->lines_data = 0;
	map->floor_color = 0;
	map->ceil_color = 0;
	map->nb_doors = 0;
}

//init an img where we will draw every pixel on it
//and then display the img on the window
void	init_img(t_my_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
}

//set up and start mlx
void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		printf("Error creating the mlx\n");
		exit(EXIT_FAILURE);
	}
	game->window = mlx_new_window(game->mlx, WIDTH,
			HEIGHT, "cub3d");
	if (game->window == NULL)
	{
		free(game->window);
		exit(EXIT_FAILURE);
	}
	init_img(&game->screen_img);
}

void	init_pos_player(t_game *game)
{
	char	pos;
	int		i;
	int		j;
	int		x;

	x = 0;
	i = -1;
	while (++i < game->map.rows - 1)
	{
		j = -1;
		while (++j < game->map.col_max - 1 && game->map.map[i][j])
		{
			pos = game->map.map[i][j];
			if (pos == 'D')
			{
				game->map.door_pos_x[x] = j;
				game->map.door_pos_y[x++] = i;
			}
			else if (pos == 'N' || pos == 'S' || pos == 'W' || pos == 'E')
			{
				game->player.pos_x = j;
				game->player.pos_y = i;
			}
		}
	}
}

//close mlx and free everything
int	end_game(t_game *game)
{
	int	i;

	free_map(&game->map);
	mlx_destroy_window(game->mlx, game->window);
	i = -1;
	while (++i < 4)
	{
		if (game->wall[i].img)
			mlx_destroy_image(game->mlx, game->wall[i].img);
	}
	i = -1;
	while (++i < 8)
	{
		if (game->torch[i].img)
			mlx_destroy_image(game->mlx, game->torch[i].img);
	}
	if (game->screen_img.mlx_img)
		mlx_destroy_image(game->mlx, game->screen_img.mlx_img);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}
