/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:12:45 by pmenard           #+#    #+#             */
/*   Updated: 2025/06/26 16:12:46 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	free_txt(char **arr)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_map(t_map *map)
{
	if (map->data)
		free_arr(map->data);
	if (map->map)
		free_arr(map->map);
	if (map->rgb)
		free_arr(map->rgb);
	if (map->txt)
		free_txt(map->txt);
	if (map->door_pos_x)
		free(map->door_pos_x);
	if (map->door_pos_y)
		free(map->door_pos_y);
}

void	free_and_exit(t_map *map, int code)
{
	free_map(map);
	exit(code);
}

void	free_arr(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (i < arrlen(arr))
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}
