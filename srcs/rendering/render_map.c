#include "../../cub3d.h"

// draw_wall(int *img)
// {
// 	*img = color;
// }

// void	draw_all()
// {
// 	int *img;

// 	img = img;
// 	while (++y < HEIGHT)
// 	{
// 		while (++x < WIDTH)
// 		{
// 			data->camera[x];
// 			if (y < camera.draw_start)
// 				//draw_ceilcolor
// 			else if (y > camera.draw_end)
// 				//draw_floorcolor
// 			else
// 				//draw_wall
// 			img++;
// 		}
// 	}
// }

//draw background split horizontaly
//top half is the ceiling
//bottom half is the floor
void	render_background(t_my_img *img, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			put_pixel(img, j, i, map->ceil_color);
			j++;
		}
		i++;
	}
	i = HEIGHT / 2;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			put_pixel(img, j, i, map->floor_color);
			j++;
		}
		i++;
	}
}

void	get_door_pos(t_map *map)
{
	int		i;
	int		j;
	int		x;

	x = 0;
	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == 'D')
			{
				map->door_pos_x[x] = j;
				map->door_pos_y[x] = i;
				x++;
				if (x == map->nb_doors)
					break;
			}
		}
	}
}

void	alter_door_map(t_map *map)
{

}

//check distance between player and door using Manhattan distance algorithm
void	check_distance_door(t_map *map, t_player *player)
{
	float	*distance;
	int		i;

	get_door_pos(map);
	distance = ft_calloc(sizeof(float), map->nb_doors);
	i = 0;
	while (i < map->nb_doors)
	{
		distance[i] = fabs(player->pos_x - map->door_pos_x[i])
			+ fabs(player->pos_y - map->door_pos_y[i]);
		if (distance[i] <= 3)
		{
			alter_door_map(map);
		}
		i++;
	}
	free(distance);
}

//render the 3d img of the map
void	render_map(t_game *game)
{
	if (game->screen_img.mlx_img)
		mlx_destroy_image(game->mlx, game->screen_img.mlx_img);
	game->screen_img.mlx_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->screen_img.addr = mlx_get_data_addr(game->screen_img.mlx_img,
			&game->screen_img.bpp, &game->screen_img.line_len,
			&game->screen_img.endian);
	render_background(&game->screen_img, &game->map);
	check_distance_door(&game->map, &game->player);
	do_all_rays(game, &game->player.camera);
}
