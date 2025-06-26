#include "../../cub3d.h"

//render torch as animated sprite
void	render_torch(t_game *game)
{
	static int	i = 0;
	int			framerate;

	framerate = 4;
	draw_torch(game, &game->torch[i / framerate]);
	i++;
	if (i == 8 * framerate)
		i = 0;
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
	int		clear;
	int		x;
	int		y;
	int		size;

	clear = 0xFF000000;
	size = WIDTH / 160;
	y = 10;
	while (y < tex->height - 10)
	{
		x = 0;
		while (x < tex->width)
		{
			game->screen_img.color = get_tex_pixel_color(tex, x,
					tex->height - y);
			if (game->screen_img.color != clear && (x + size) * size < WIDTH
				&& y * size < HEIGHT)
				draw_pixel_torch(&game->screen_img, x + size, y - 10, size);
			x++;
		}
		y++;
	}
}
