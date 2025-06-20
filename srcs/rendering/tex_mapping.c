#include "../../cub3d.h"

int	get_img_pixel_color(t_my_img *img, int x, int y)
{
	char			*pixel;
	unsigned int	color;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *) pixel;
	printf("%spixel%s : %d\n", RED, NC, color);
	return (color);
}

t_texture	*get_wall_tex(t_game *game, t_camera *camera)
{
	if (camera->side_touch == VERTICAL && camera->dir[X] > 0)
		return (&game->wall[WALL_W]);
	else if (camera->side_touch == VERTICAL && camera->dir[X] < 0)
		return (&game->wall[WALL_E]);
	else if (camera->side_touch == HORIZONTAL && camera->dir[Y] > 0)
		return (&game->wall[WALL_N]);
	else if (camera->side_touch == HORIZONTAL && camera->dir[Y] < 0)
		return (&game->wall[WALL_S]);
	return (NULL);
}

void	get_wall_x(t_game *game, t_tex_mapping *tex)
{
	t_camera	*camera;
	t_player	*player;

	camera = &game->player.camera;
	player = &game->player;
	if (camera->side_touch == VERTICAL)
		tex->itpl_x[WALL] = player->pos_y + camera->raylen * camera->ray_dir[Y];
	else
		tex->itpl_x[WALL] = player->pos_x + camera->raylen * camera->ray_dir[X];
	tex->itpl_x[WALL] -= floor(tex->itpl_x[WALL]);
}

void	get_tex_x(t_camera *camera, t_tex_mapping *tex)
{
	tex->itpl_x[TEX] = (int)(tex->itpl_x[WALL] * (double)SIZE);
	if (camera->side_touch == VERTICAL && camera->ray_dir[X] > 0)
		tex->itpl_x[TEX] = tex->tex->width - tex->itpl_x[TEX] - 1;
	if (camera->side_touch == HORIZONTAL && camera->ray_dir[X] < 0)
		tex->itpl_x[TEX] = tex->tex->width - tex->itpl_x[TEX] - 1;
}
