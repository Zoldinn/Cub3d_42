#include "../../cub3d.h"

//draw one (and only one) pixel
void	put_pixel(t_my_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
	//return color for xpm
}

//draw a square of pixels
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

// draw_wall(int *img)
// {
// 	*img = color;
// }

// void	draw_all()
// {
// 	int *img;

// 	img = img;
// 	while (++y < HEIGHT)
// 	{
// 		while (++x < WIDTH)
// 		{
// 			data->camera[x];
// 			if (y < camera.draw_start)
// 				//draw_ceilcolor
// 			else if (y > camera.draw_end)
// 				//draw_floorcolor
// 			else
// 				//draw_wall
// 			img++;
// 		}
// 	}
// }

//draw background split horizontaly
//top half is the ceiling
//bottom half is the floor
void	render_background(t_my_img *img, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			put_pixel(img, j, i, map->ceil_color);
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
			put_pixel(img, j, i, map->floor_color);
			j++;
		}
		i++;
	}
}

//render the 3d img of the map
void	render_map(t_game *game)
{
	if (game->screen_img.mlx_img)
		mlx_destroy_image(game->mlx, game->screen_img.mlx_img);
	game->screen_img.done = 0;
	game->screen_img.mlx_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->screen_img.addr = mlx_get_data_addr(game->screen_img.mlx_img,
			&game->screen_img.bpp, &game->screen_img.line_len,
			&game->screen_img.endian);
	render_background(&game->screen_img, &game->map);
	raycasting(game, &game->player.camera);
}
