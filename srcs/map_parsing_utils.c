#include "../cub3d.h"

void	find_start_map(t_map *map, int *i, char **temp)
{
	char	**arr;

	while (*i >= 0)
	{
		arr = ft_split(temp[*i], " \t\n");
		if (arr[0])
		{
			if (ft_strlen(arr[0]) < 3 && (ft_strchr(temp[*i], '/') != NULL
					|| ft_strchr(temp[*i], ',') != NULL))
			{
				free_arr(arr);
				break ;
			}
		}
		free_arr(arr);
		(*i)--;
	}
	map->start_map = *i;
}

void	find_end_map(t_map *map, int *i, char **temp)
{
	int		j;

	j = 0;
	(*i)++;
	while (temp[*i])
	{
		if (temp[*i][0] == '\n')
			break ;
		map->map[j++] = ft_strdup(temp[*i]);
		map->rows++;
		(*i)++;
	}
}

void	error_in_comparing(t_map *map, char *temp, char *file_temp)
{
	free(temp);
	free(file_temp);
	p_er("Empty lines are not allowed in the map");
	free_and_exit(map, 1);
}

//compare maps from structure (no '\n') and map from file to see if there
//are any empty lines
void	compare_maps(t_map *map, char *file_temp, int i)
{
	char	*temp;
	int		j;
	int		index_map;

	index_map = 0;
	while (map->map[index_map])
	{
		j = i;
		while (file_temp[j] != '\n')
			j++;
		temp = ft_substr(file_temp, i, j - i);
		i += (j - i) + 1;
		if (ft_cmpstr(map->map[index_map], temp) != 0 || temp[0] == '\n')
			error_in_comparing(map, temp, file_temp);
		if (!temp || temp[0] == '\0')
		{
			free(temp);
			break ;
		}
		free(temp);
		index_map++;
	}
}

//set file_temp to be compared in compare_maps
void	check_empty_lines_map(t_map *map, char *file_temp)
{
	int	i;
	int	j;

	i = ft_strlen(file_temp) - 1;
	while (file_temp[i] == '\n')
		i--;
	i++;
	j = 0;
	while (j < map->rows && i >= 0)
	{
		if (file_temp[i] == '\n')
			j++;
		i--;
	}
	if (j != map->rows)
	{
		p_er("Empty lines are not allowed in the map");
		free(file_temp);
		free_and_exit(map, 1);
	}
	while (i >= 0 && file_temp[i] != '\n')
		i--;
	i++;
	compare_maps(map, file_temp, i);
	free(file_temp);
}
