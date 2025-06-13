#include "../../cub3d.h"

void	pix_put(t_image *img, int x, int y, int color)
{
	char	*pixel;
	
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	render_background(t_image *img)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < WIDTH / 2)
	{
		j = 0;
		while (j < (HEIGHT / 2))
		{
			pix_put(img, j, i, WALL_COLOR);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < WIDTH)
	{
		j = HEIGHT / 2;
		while (j < HEIGHT)
		{
			pix_put(img, j, i, FLOOR_COLOR);
			j++;
		}
		i++;
	}
}

void	init_img(t_image *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
}

void	render_map(t_game *game)
{
	init_img(&game->img);
	game->img.mlx_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.mlx_img, &game->img.bpp,
		&game->img.line_len , &game->img.endian);
	render_background(&game->img);
	mlx_put_image_to_window(game->mlx, game->window, game->img.mlx_img, 0, 0);
}
