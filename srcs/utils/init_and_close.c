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
	game->player.pos_x = -1;
	game->player.pos_y = -1;
	init_img(&game->map2d_img);
	init_img(&game->map3d_img);
}

void	init_direction_player(t_game *game)
{
	game->player.go_up = 0;
	game->player.go_down = 0;
	game->player.go_right = 0;
	game->player.go_left = 0;
}

//close mlx and free everything
int	end_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	if (game->txt[WALL].img)
		mlx_destroy_image(game->mlx, game->txt[WALL].img);
	if (game->txt[FLOOR].img)
		mlx_destroy_image(game->mlx, game->txt[FLOOR].img);
	if (game->txt[EMPTY].img)
		mlx_destroy_image(game->mlx, game->txt[EMPTY].img);
	if (game->player.texture.img)
		mlx_destroy_image(game->mlx, game->player.texture.img);
	if (game->txt[OOB].img)
		mlx_destroy_image(game->mlx, game->txt[OOB].img);
	if (game->map3d_img.mlx_img)
		mlx_destroy_image(game->mlx, game->map3d_img.mlx_img);
	if (game->map2d_img.mlx_img)
		mlx_destroy_image(game->mlx, game->map2d_img.mlx_img);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_map(&game->map);
	exit(EXIT_SUCCESS);
	return (0);
}
