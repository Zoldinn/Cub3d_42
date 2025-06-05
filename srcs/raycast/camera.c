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

}

int	**get_raydirs(t_game *game)
{
	
}