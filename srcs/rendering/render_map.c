#include "../../cub3d.h"

void	put_pixel(t_my_img *img, int x, int y, int color)
{
	char	*pixel;
	
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	draw_square(t_my_img *img, double x, double y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			put_pixel(img, (SIZE * y) + i, (SIZE * x) + j, color);
			j++;
		}
		i++;
	}
}

void	render_background(t_my_img *img)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			put_pixel(img, j, i, BLUE_COLOR);
			j++;
		}
		i++;
	}
	i = HEIGHT / 2;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			put_pixel(img, j, i, FLOOR_COLOR);
			j++;
		}
		i++;
	}
}

void	render_map(t_game *game)
{
	if (game->map3d_img.mlx_img)
		mlx_destroy_image(game->mlx, game->map3d_img.mlx_img);
	game->map3d_img.mlx_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->map3d_img.addr = mlx_get_data_addr(game->map3d_img.mlx_img,
		&game->map3d_img.bpp, &game->map3d_img.line_len,
		&game->map3d_img.endian);
	render_background(&game->map3d_img);
	mlx_put_image_to_window(game->mlx, game->window, game->map3d_img.mlx_img,
		0, 0);
}
