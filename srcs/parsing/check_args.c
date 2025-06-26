/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:13:59 by pmenard           #+#    #+#             */
/*   Updated: 2025/06/26 16:13:59 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

int	check_args(int argc, char **argv)
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

int	is_valid_letter_map(t_map *map, int i, int j)
{
	if (map->map[i][j] == '0' || map->map[i][j] == '1'
		|| map->map[i][j] == 'N' || map->map[i][j] == 'S'
		|| map->map[i][j] == 'E' || map->map[i][j] == 'W'
		|| map->map[i][j] == ' ' || map->map[i][j] == 'D')
		return (0);
	else
		return (1);
}
