#include "../../cub3d.h"

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
	game->window = mlx_new_window(game->mlx, (game->map.col_max + 1) * SIZE,
			game->map.rows * SIZE, "cub3d");
	if (game->window == NULL)
	{
		free(game->window);
		exit(EXIT_FAILURE);
	}
	game->player.pos_x = 0;
	game->player.pos_y = 0;
}

//close mlx and free everything
int	end_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	if (game->wall.img)
		mlx_destroy_image(game->mlx, game->wall.img);
	if (game->floor.img)
		mlx_destroy_image(game->mlx, game->floor.img);
	if (game->empty.img)
		mlx_destroy_image(game->mlx, game->empty.img);
	if (game->player.texture.img)
		mlx_destroy_image(game->mlx, game->player.texture.img);
	if (game->oob.img)
		mlx_destroy_image(game->mlx, game->oob.img);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_map(&game->map);
	exit(EXIT_SUCCESS);
	return (0);
}
