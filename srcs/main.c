#include "../cub3d.h"

int	check_extension(char *file_name, char *ext)
{
	int		len;
	char	*clean;

	clean = ft_strtrim(file_name, " \t");
	len = ft_strlen(clean);
	if (len <= 4)
		return (free(clean), p_er(""), printf("file type isn't %s\n", ext), 1);
	else if (clean[len - 4] != ext[0]
		|| clean[len - 3] != ext[1]
		|| clean[len - 2] != ext[2]
		|| clean[len - 1] != ext[3]
		|| clean[len] != '\0')
		return (free(clean), p_er(""), printf("file type isn't %s\n", ext), 1);
	return (free(clean), 0);
}

static int	check_args(int argc, char **argv)
{
	if (argc < 2)
	{
		p_er("An argument including a map in .cub format is required.");
		return (1);
	}
	else if (argc > 2)
		return (p_er("Too many arguments."), 1);
	else
	{
		if (ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])) == NULL)
			return (p_er("Map file isn't .cub"), 1);
	}
	if (check_extension(argv[1], ".cub") != 0)
		return (p_er("Map file isn't .cub"), 1);
	return (0);
}

int	check_move(t_game *game, int x, int y)
{
	if (game->map.map[y][x] == ' ' || game->map.map[y][x] == '\0')
		return (1);
	else
		return (0);
}

//check if the movement of the player is valid
//0 is valid
//1 is not valid
int	check_player_move(t_game *game, int keysym)
{
	double	x;
	double	y;

	x = game->player.pos_x;
	y = game->player.pos_y;
	if (keysym == KEY_W)
		y -= 0.1f;
	else if (keysym == KEY_S)
		y += 1;
	else if (keysym == KEY_A)
		x -= 0.1f;
	else if (keysym == KEY_D)
		x += 1;
	if (game->map.map[(int)y][(int)x] == ' ' || !game->map.map[(int)y][(int)x])
		return (1);
	else
		return (0);
}

//get pressed key and set new position of the player
void	move_player(int keysym, t_game *game)
{
	if (keysym == KEY_W && game->player.pos_y > 0
		&& check_player_move(game, keysym) == 0)
		game->player.pos_y -= .1f;
	else if (keysym == KEY_S && game->player.pos_y < game->map.rows - 1
		&& check_player_move(game, keysym) == 0)
		game->player.pos_y += .1f;
	else if (keysym == KEY_A && game->player.pos_x > 0
		&& check_player_move(game, keysym) == 0)
		game->player.pos_x -= .1f;
	else if (keysym == KEY_D && game->player.pos_x < game->map.col_max
		&& check_player_move(game, keysym) == 0)
		game->player.pos_x += .1f;
}

void	move_camera(int keysym, t_game *game)
{
	if (keysym == KEY_LEFT)
	{
		game->player.camera.angle_rad -= .1f;
	}
	else if (keysym == KEY_RIGHT)
	{
		game->player.camera.angle_rad += .1f;
	}
}

//called by mlx_hook when a key is pressed
int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == KEY_ESC)
		end_game(game);
	if (keysym == KEY_W || keysym == KEY_A || keysym == KEY_S
		|| keysym == KEY_D || keysym == KEY_LEFT || keysym == KEY_RIGHT)
	{
		move_player(keysym, game);
		move_camera(keysym, game);
		update_camera_dir(&game->player.camera);
		render_map(game);
		render_map2d(game);
	}
	return (0);
}

void	init(t_game *game)
{
	init_game(game);
	init_texture(game);
	init_pos_player(game);
	init_camera_angle(&game->player.camera, &game->map);
	update_camera_dir(&game->player.camera);
	render_map(game);
	render_map2d(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_map(&game.map);
	if (check_args(argc, argv) != 0)
		return (free_map(&game.map), 1);
	if (check_file(argv[1], &game.map) != 0)
		return (free_map(&game.map), 1);
	init(&game);
	mlx_hook(game.window, DestroyNotify, StructureNotifyMask,
		&end_game, &game);
	mlx_hook(game.window, KeyPress, KeyPressMask, &handle_keypress, &game);
	mlx_loop(game.mlx);
	free_map(&game.map);
	return (0);
}
