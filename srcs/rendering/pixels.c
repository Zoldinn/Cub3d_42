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
			put_pixel(img, (SIZE * y) + i, (SIZE * x) + j, color);
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

void	draw_torch(t_game *game, t_texture *tex, int a, int transparent)
{
	int		color;
	int		x;
	int		y;

	y = 0;
	while (y < tex->height)
	{
		x = 0;
		while (x < tex->width)
		{
			color = get_tex_pixel_color(tex, x, y);
			if (color != transparent)
				draw_square(&game->screen_img, y + a, x + a, color);
			x++;
		}
		y++;
	}
}
