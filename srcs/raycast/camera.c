/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:13:08 by lefoffan          #+#    #+#             */
/*   Updated: 2025/06/26 16:13:09 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	get_player_initial_dir(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < (int) ft_strlen(map->map[i]))
		{
			if (is_charset(map->map[i][j], "NSWE"))
				return (map->map[i][j]);
		}
	}
	return ('\0');
}

double	get_rad(double degree)
{
	return ((degree * PI) / 180);
}

// North and south are reversed (because axe Y is reversed)
void	init_camera_angle(t_camera *camera, t_map *map)
{
	char	player;

	player = get_player_initial_dir(map);
	if (player == 'N')
		camera->angle_rad = (3 * PI) / 2;
	else if (player == 'S')
		camera->angle_rad = PI / 2;
	else if (player == 'W')
		camera->angle_rad = PI;
	else if (player == 'E')
		camera->angle_rad = 0;
}

void	update_camera_dir(t_camera *camera)
{
	double	fov_rad;

	fov_rad = get_rad((double) FOV_DEGREE);
	camera->dir[X] = cos(camera->angle_rad);
	camera->dir[Y] = sin(camera->angle_rad);
	camera->plane[X] = -camera->dir[Y] * tan(fov_rad / 2);
	camera->plane[Y] = camera->dir[X] * tan(fov_rad / 2);
}

void	move_camera(int keysym, t_game *game)
{
	if (keysym == KEY_LEFT)
		game->player.camera.angle_rad -= .05f;
	else if (keysym == KEY_RIGHT)
		game->player.camera.angle_rad += .05f;
}
