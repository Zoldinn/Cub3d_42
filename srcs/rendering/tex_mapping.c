/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:13:32 by pmenard           #+#    #+#             */
/*   Updated: 2025/06/26 16:13:32 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	get_tex_pixel_color(t_texture *tex, int x, int y)
{
	char			*pixel;
	unsigned int	color;

	if (x < 0 || y < 0 || !tex || !tex->addr
		|| tex->height == 0 || tex->width == 0
		|| y > tex->height || x > tex->width)
		return (0);
	pixel = tex->addr + (y * tex->size_line + x * (tex->bpp / 8));
	color = *(unsigned int *) pixel;
	return (color);
}

t_texture	*get_wall_tex(t_game *game, t_camera *camera)
{
	if (camera->side_touch == VERTICAL && camera->step[X] > 0)
		return (&game->wall[WALL_E]);
	else if (camera->side_touch == VERTICAL && camera->step[X] < 0)
		return (&game->wall[WALL_W]);
	else if (camera->side_touch == HORIZONTAL && camera->step[Y] > 0)
		return (&game->wall[WALL_S]);
	else if (camera->side_touch == HORIZONTAL && camera->step[Y] < 0)
		return (&game->wall[WALL_N]);
	return (NULL);
}

void	get_wall_x(t_game *game, t_tex_mapping *tex)
{
	t_camera	*camera;
	t_player	*player;

	camera = &game->player.camera;
	player = &game->player;
	if (camera->side_touch == VERTICAL)
		tex->x[WALL] = player->pos_y + camera->raylen * camera->ray_dir[Y];
	else
		tex->x[WALL] = player->pos_x + camera->raylen * camera->ray_dir[X];
	tex->x[WALL] -= floor(tex->x[WALL]);
}

void	get_tex_x(t_camera *camera, t_tex_mapping *tex)
{
	tex->x[TEX] = (int)(tex->x[WALL] * (double)tex->tex->width);
	if (camera->side_touch == VERTICAL && camera->ray_dir[X] < 0)
		tex->x[TEX] = tex->tex->width - tex->x[TEX] - 1;
	if (camera->side_touch == HORIZONTAL && camera->ray_dir[Y] > 0)
		tex->x[TEX] = tex->tex->width - tex->x[TEX] - 1;
}
