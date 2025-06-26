#include "../../cub3d.h"

//draw one (and only one) pixel
void	put_pixel(t_my_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
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
			put_pixel(img, (SIZE * x) + i, (SIZE * y) + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_my_img *img, double x, double y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			put_pixel(img, (SIZE * y) + i - (SIZE / 2),
				(SIZE * x) + j - (SIZE / 2), color);
			j++;
		}
		i++;
	}
}

void	draw_pixel_torch(t_my_img *img, int x, int y, int size)
{
	int	i;
	int	j;
	int	height;

	height = HEIGHT - (size * y);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(img, (size * x) + i, height + j, img->color);
			j++;
		}
		i++;
	}
}

void	draw_torch(t_game *game, t_texture *tex)
{
	int		transparent;
	int		x;
	int		y;
	int		size;

	transparent = 0xFF000000;
	size = WIDTH / 160;
	y = 10;
	while (y < tex->height - 10)
	{
		x = 0;
		while (x < tex->width)
		{
			game->screen_img.color = get_tex_pixel_color(tex, x,
				tex->height - y);
			if (game->screen_img.color != transparent && (x + size) * size < WIDTH
				&& y * size < HEIGHT)
				draw_pixel_torch(&game->screen_img, x + size, y - 10, size);
			x++;
		}
		y++;
	}
}
