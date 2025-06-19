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

void	move_camera(int keysym, t_game *game)
{
	if (keysym == KEY_LEFT)
		game->player.camera.angle_rad -= .1f;
	else if (keysym == KEY_RIGHT)
		game->player.camera.angle_rad += .1f;
}

//called by mlx_hook when a key is pressed
int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == KEY_ESC)
		end_game(game);
	if (keysym == KEY_W || keysym == KEY_A || keysym == KEY_S
		|| keysym == KEY_D)
	{
		move_player(keysym, game);
		render_map(game);
		render_map2d(game);
	}
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	(void)y;
	if (x < (WIDTH / 2) - (WIDTH / 10))
		game->player.camera.angle_rad -= 0.1f;
	else if (x > (WIDTH / 2) + (WIDTH / 10))
		game->player.camera.angle_rad += 0.1f;
	else
		return (0);
	update_camera_dir(&game->player.camera);
	render_map(game);
	render_map2d(game);
	mlx_mouse_move(game->mlx, game->window, WIDTH / 2, HEIGHT / 2);
	return (0);
}

void	init(t_game *game)
{
	init_game(game);
	get_textures_wall(game);
	game->map.floor_color = rgb_to_hex(game->map.rgb[0]);
	game->map.ceil_color = rgb_to_hex(game->map.rgb[1]);
	init_texture(game);
	init_pos_player(game);
	init_camera_angle(&game->player.camera, &game->map);
	update_camera_dir(&game->player.camera);
	render_map(game);
	render_map2d(game);
	mlx_mouse_hide(game->mlx, game->window);
	mlx_mouse_move(game->mlx, game->window, WIDTH / 2, HEIGHT / 2);
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
	mlx_hook(game.window, 6, PointerMotionMask, &mouse_move, &game);
	mlx_hook(game.window, KeyPress, KeyPressMask, &handle_keypress, &game);
	mlx_loop(game.mlx);
	free_map(&game.map);
	return (0);
}
