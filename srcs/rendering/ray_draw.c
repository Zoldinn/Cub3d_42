#include "../../cub3d.h"

int	get_img_pixel(t_my_img *img, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *) pixel;
	return (color);
}

void	get_side_img(t_game *game, t_camera *camera, t_wall *wall)
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

void	draw_vertical_line(t_my_img *img, t_game *game, t_camera *camera)
{
	t_wall	wall;
	int		y;

	y = camera->draw_start;
	while (y <= camera->draw_end)
	{
		camera->color = get_img_pixel(get_side_img(game, camera), camera->x, y);
		if (camera->side_touch == HORIZONTAL)
			camera->color /= 2;
		put_pixel(img, camera->x, y, camera->color);
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

