#include "../cub3d.h"

int	get_img_pixel_color(t_my_img *img, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *) pixel;
	return (color);
}

void	get_wall_tex(t_game *game, t_camera *camera, t_wall *wall)
{
	if (camera->side_touch == VERTICAL && camera->dir[X] > 0)
		wall->tex = &game->wall[WALL_W];
	else if (camera->side_touch == VERTICAL && camera->dir[X] < 0)
		wall->tex = &game->wall[WALL_E];
	else if (camera->side_touch == HORIZONTAL && camera->dir[Y] > 0)
		wall->tex = &game->wall[WALL_N];
	else if (camera->side_touch == HORIZONTAL && camera->dir[Y] < 0)
		wall->tex = &game->wall[WALL_S];
}

void	get_wall_x(t_game *game, t_wall *wall)
{
	t_camera	*camera;
	t_player	*player;

	camera = &game->player.camera;
	player = &game->player;
	if (camera->side_touch == VERTICAL)
		wall->wall_x = player->pos_y + camera->raylength * camera->ray_dir[Y];
	else
		wall->wall_x = player->pos_x + camera->raylength * camera->ray_dir[X];
	wall->wall_x -= floor(wall->wall_x);
}

void	get_tex_x(t_game *game, t_wall *wall)
{
	t_camera	*camera;

	wall->tex_x = (int)(wall->wall_x * (double)SIZE);
	if (camera->side_touch == VERTICAL && camera->ray_dir[X] > 0)
		wall->tex_x = wall->tex->width - wall->tex_x - 1;
	if (camera->side_touch == HORIZONTAL && camera->ray_dir[X] < 0)
		wall->tex_x = wall->tex->width - wall->tex_x - 1;
}
