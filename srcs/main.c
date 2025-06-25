#include "../cub3d.h"

//called by mlx_hook when a key is pressed
int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == KEY_ESC)
		end_game(game);
	if (keysym == KEY_W || keysym == KEY_A || keysym == KEY_S
		|| keysym == KEY_D || keysym == KEY_LEFT || keysym == KEY_RIGHT)
	{
		if (keysym == KEY_LEFT || keysym == KEY_RIGHT)
		{
			move_camera(keysym, game);
			update_camera_dir(&game->player.camera);
		}
		move_player(keysym, game);
	}
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	(void)y;
	if (x < (WIDTH / 2) - (WIDTH / 12))
		game->player.camera.angle_rad -= 0.1f;
	else if (x > (WIDTH / 2) + (WIDTH / 12))
		game->player.camera.angle_rad += 0.1f;
	else
		return (0);
	update_camera_dir(&game->player.camera);
	mlx_mouse_move(game->mlx, game->window, WIDTH / 2, HEIGHT / 2);
	return (0);
}

int	render_loop(t_game *game)
{
	render_map(game);
	render_map2d(game);
	render_torch(game);
	mlx_put_image_to_window(game->mlx, game->window, game->screen_img.mlx_img,
		0, 0);
	return (0);
}

void	init(t_game *game)
{
	init_game(game);
	get_textures_wall(game);
	game->map.floor_color = rgb_to_hex(game->map.rgb[0]);
	game->map.ceil_color = rgb_to_hex(game->map.rgb[1]);
	game->map.door_pos_x = ft_calloc(sizeof(int), game->map.nb_doors);
	game->map.door_pos_y = ft_calloc(sizeof(int), game->map.nb_doors);
	init_texture(game);
	init_pos_player(game);
	init_camera_angle(&game->player.camera, &game->map);
	update_camera_dir(&game->player.camera);
	render_map(game);
	render_map2d(game);
	render_torch(game);
	mlx_put_image_to_window(game->mlx, game->window, game->screen_img.mlx_img,
		0, 0);
	// mlx_mouse_hide(game->mlx, game->window);
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
	mlx_loop_hook(game.mlx, &render_loop, &game);
	mlx_loop(game.mlx);
	free_map(&game.map);
	return (0);
}
