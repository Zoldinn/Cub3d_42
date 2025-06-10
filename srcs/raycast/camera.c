#include "../../cub3d.h"

char	get_player_init_dir(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map.rows)
	{
		j = -1;
		while (++j < ft_strlen(game->map.map[i]))
		{
			if (is_charset(game->map.map[i][j], "NSWE"))
				return (game->map.map[i][j]);
		}
	}
	return (0);
}

// North and south are reversed (because axe Y is reversed)
void	init_camera_angle(t_game *game)
{
	char	player;

	player = get_initial_dir(game);
	if (player == 'N')
		game->player.camera.angle_rad = (3 * PI) / 2;
	else if (player == 'S')
		game->player.camera.angle_rad = PI / 2;
	else if (player == 'W')
		game->player.camera.angle_rad = PI;
	else if (player == 'E')
		game->player.camera.angle_rad = 0;
}

void	update_camera_dir(t_game *game)
{
	double	*dir_x;
	double	*dir_y;
	double	*plane_x;
	double	*plane_y;
	double	*angle_rad;

	dir_x = &game->player.camera.dir_x;
	dir_y = &game->player.camera.dir_y;
	plane_x = &game->player.camera.plane_x;
	plane_y = &game->player.camera.plane_y;
	angle_rad = &game->player.camera.angle_rad;
	*dir_x = cos(*angle_rad);
	*dir_y = sin(*angle_rad);
	*plane_x = -(*dir_y) * tan(FOV_DEGREE / 2);
	*plane_y = *dir_x * tan(FOV_DEGREE / 2);
}

int	*get_raydir_x(t_game *game, int x)
{
	int		*raydirs;
	double	camera_x;
	double	*dir[2];
	double	*plane[2];

	raydirs = malloc(sizeof(int) * 2);
	if (!raydirs)
		return (NULL);
	dir[X] = &game->player.camera.dir_x;
	dir[Y] = &game->player.camera.dir_y;
	plane[X] = &game->player.camera.plane_x;
	plane[Y] = &game->player.camera.plane_y;
	camera_x = 2 * x / (double) game->map.col_max - 1;
	raydirs[X] = *dir[X] + *plane[X] * camera_x;
	raydirs[Y] = *dir[Y] + *plane[Y] * camera_x;
	return (raydirs);
}

void	set_step_and_dir