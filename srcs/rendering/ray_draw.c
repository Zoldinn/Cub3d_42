#include "../../cub3d.h"

// set the height of the wall, the start/end drawing point
void	set_drawing_height(t_tex_mapping *tex, t_camera *camera)
{
	tex->line_height = (int) (HEIGHT / camera->raylen);
	tex->draw_start = (HEIGHT / 2) - (tex->line_height / 2);
	if (tex->draw_start < 0)
		tex->draw_start = 0;
	tex->draw_end = (HEIGHT / 2) + (tex->line_height / 2);
	if (tex->draw_end >= HEIGHT)
		tex->draw_end = HEIGHT - 1;
}

// use a bresenham like
void	draw_vertical_line(t_my_img *img, t_game *game, t_camera *camera)
{
	t_tex_mapping	tex;
	int				y;

	tex.tex = get_wall_tex(game, camera);
	set_drawing_height(&tex, camera);
	get_wall_x(game, &tex);
	get_tex_x(camera, &tex);
	tex.step = (tex.tex->height << 8) / tex.line_height;
	tex.float_y = (tex.draw_start - HEIGHT / 2 + tex.line_height / 2) * tex.step;
	y = tex.draw_start;
	while (y <= tex.draw_end)
	{
		tex.int_y = (tex.float_y >> 8) & (tex.tex->height - 1);
		tex.color = get_img_pixel_color(tex.tex->img, (int)tex.itpl_x[TEX], tex.int_y);
		if (camera->side_touch == VERTICAL)
			tex.color = (tex.color >> 1) & 0x7F7F7F;
		put_pixel(img, camera->x, y, tex.color);
		tex.float_y += tex.step;
		y++;
	}
}

//draw a cone of pixels in order to see raycasting
void	draw_ray(t_game *game, int color)
{
	double		camera_x;
	double		ray_dir[2];
	double		ray[2];
	t_camera	*camera;
	int			x;

	camera = &game->player.camera;
	x = -1;
	while (++x < WIDTH)
	{
		camera_x = 2 * x / (double) game->map.col_max - 1;
		ray_dir[X] = camera->dir[X] + camera->plane[X] * camera_x;
		ray_dir[Y] = camera->dir[Y] + camera->plane[Y] * camera_x;
		ray[X] = game->player.pos_x;
		ray[Y] = game->player.pos_y;
		while (game->map.map[(int)ray[Y]][(int)ray[X]] != '1')
		{
			put_pixel(&game->screen_img, ray[X] * SIZE,
				ray[Y] * SIZE, color);
			ray[Y] += ray_dir[Y] * 0.01;
			ray[X] += ray_dir[X] * 0.01;
		}
	}
}

