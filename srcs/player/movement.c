/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:13:42 by pmenard           #+#    #+#             */
/*   Updated: 2025/06/26 16:13:44 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

//predict movement and set it in x and y
//useful for checking movement in check_player_move
void	set_movement(t_game *game, int keysym, double *x, double *y)
{
	if (keysym == KEY_W)
	{
		*x = game->player.pos_x + (game->player.camera.dir[X] * SPEED);
		*y = game->player.pos_y + (game->player.camera.dir[Y] * SPEED);
	}
	else if (keysym == KEY_S)
	{
		*x = game->player.pos_x - (game->player.camera.dir[X] * SPEED);
		*y = game->player.pos_y - (game->player.camera.dir[Y] * SPEED);
	}
	else if (keysym == KEY_A)
	{
		*x = game->player.pos_x - (game->player.camera.plane[X] * SPEED);
		*y = game->player.pos_y - (game->player.camera.plane[Y] * SPEED);
	}
	else if (keysym == KEY_D)
	{
		*x = game->player.pos_x + (game->player.camera.plane[X] * SPEED);
		*y = game->player.pos_y + (game->player.camera.plane[Y] * SPEED);
	}
}

//check if the movement of the player is valid
//0 is valid
//1 is not valid
int	check_player_move(t_game *game, int keysym)
{
	double	x;
	double	y;
	int		offset_oob;

	x = 0;
	y = 0;
	set_movement(game, keysym, &x, &y);
	offset_oob = 2;
	if (x <= 0 || y <= 0 || x >= game->map.col_max || y >= game->map.rows - 1)
		return (1);
	if (game->map.map[(int)y][(int)x] == ' '
		|| game->map.map[(int)y][(int)x] == '1'
		|| (size_t)x > ft_strlen(game->map.map[(int)y]) - offset_oob)
		return (1);
	return (0);
}

//get pressed key and set new position of the player
void	move_player(int keysym, t_game *game)
{
	if (keysym == KEY_W && check_player_move(game, keysym) == 0)
	{
		game->player.pos_x += game->player.camera.dir[X] * SPEED;
		game->player.pos_y += game->player.camera.dir[Y] * SPEED;
	}
	else if (keysym == KEY_S && check_player_move(game, keysym) == 0)
	{
		game->player.pos_x -= game->player.camera.dir[X] * SPEED;
		game->player.pos_y -= game->player.camera.dir[Y] * SPEED;
	}
	else if (keysym == KEY_A && check_player_move(game, keysym) == 0)
	{
		game->player.pos_x -= game->player.camera.plane[X] * SPEED;
		game->player.pos_y -= game->player.camera.plane[Y] * SPEED;
	}
	else if (keysym == KEY_D && check_player_move(game, keysym) == 0)
	{
		game->player.pos_x += game->player.camera.plane[X] * SPEED;
		game->player.pos_y += game->player.camera.plane[Y] * SPEED;
	}
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->input.w = 1;
	if (keycode == KEY_S)
		game->input.s = 1;
	if (keycode == KEY_A)
		game->input.a = 1;
	if (keycode == KEY_D)
		game->input.d = 1;
	if (keycode == KEY_LEFT)
		game->input.left = 1;
	if (keycode == KEY_RIGHT)
		game->input.right = 1;
	if (keycode == KEY_ESC)
		end_game(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->input.w = 0;
	if (keycode == KEY_S)
		game->input.s = 0;
	if (keycode == KEY_A)
		game->input.a = 0;
	if (keycode == KEY_D)
		game->input.d = 0;
	if (keycode == KEY_LEFT)
		game->input.left = 0;
	if (keycode == KEY_RIGHT)
		game->input.right = 0;
	return (0);
}
