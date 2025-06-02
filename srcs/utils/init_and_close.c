#include "../cub3d.h"

void	init_map(t_map *map)
{
	map->data = NULL;
	map->map = NULL;
	map->txt = NULL;
	map->rows = 0;
	map->col_max = 0;
	map->lines_data = 0;
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
	game->window = mlx_new_window(game->mlx, (game->map.col_max + 1) * 64,
			game->map.rows * 64, "cub3d");
	if (game->window == NULL)
	{
		free(game->window);
		exit(EXIT_FAILURE);
	}
}

//close mlx and free everything
int	end_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	if (game->wall.img)
		mlx_destroy_image(game->mlx, game->wall.img);
	if (game->floor.img)
		mlx_destroy_image(game->mlx, game->floor.img);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_map(&game->map);
	exit(EXIT_SUCCESS);
	return (0);
}

//call end_game when echap is pressed
int	destroy_all(int keysym, t_game *game)
{
	if (keysym == KEY_ESC)
	{
		end_game(game);
	}
	return (0);
}
