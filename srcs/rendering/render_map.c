#include "../../cub3d.h"

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

//remove door from map if bool is set on 0
//re-add door to map if bool is set on 1
void	alter_door_map(t_map *map, int i, int bool)
{
	char	*temp;
	int		index;

	temp = ft_strdup(map->map[map->door_pos_y[i]]);
	free(map->map[map->door_pos_y[i]]);
	map->map[map->door_pos_y[i]] = ft_calloc(sizeof(char), ft_strlen(temp) + 1);
	index = 0;
	while (temp[index])
	{
		if (bool == 0 && map->door_pos_x[i] == index)
			map->map[map->door_pos_y[i]][index] = '0';
		else if (bool == 1 && map->door_pos_x[i] == index)
			map->map[map->door_pos_y[i]][index] = 'D';
		else
			map->map[map->door_pos_y[i]][index] = temp[index];
		index++;
	}
	free(temp);
}

//check distance between player and door using Manhattan distance algorithm
void	check_distance_door(t_map *map, t_player *player)
{
	float	*distance;
	int		i;

	distance = ft_calloc(sizeof(float), map->nb_doors);
	i = 0;
	while (i < map->nb_doors)
	{
		distance[i] = fabs(player->pos_x - map->door_pos_x[i])
			+ fabs(player->pos_y - map->door_pos_y[i]);
		if (distance[i] <= 3)
			alter_door_map(map, i, 0);
		else if (distance[i] > 3)
			alter_door_map(map, i, 1);
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
	raycasting(game, &game->player.camera);
}
