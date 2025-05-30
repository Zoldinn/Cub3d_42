#include "../cub3d.h"

//check if the map is valid
//x is set to know if we check '0' or not
int	check_map_map(t_map *map, int i, int j, int x)
{
	if (x == 1)
	{
		if (map->map[i][j] == '0' || map->map[i][j] == '1'
		|| map->map[i][j] == 'N' || map->map[i][j] == 'S'
		|| map->map[i][j] == 'E' || map->map[i][j] == 'W'
		|| map->map[i][j] == ' ')
			return (0);
		else
			return (p_er(""), printf("'%c' isn't valid\n", map->map[i][j]), 1);
	}
	else
	{
		if ((i < 0 || i == map->rows) || ((i + 1) == map->rows
				&& map->map[i][j] == ' ') || j < 0 || map->map[i][j] == '\0')
			return (p_er("The borders of the map are not valid\n"), 1);
		else if (map->map[i][j] == '0' || map->map[i][j] == '1'
			|| map->map[i][j] == 'N' || map->map[i][j] == 'S'
			|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			return (0);
		else if (map->map[i][j] == ' ')
			return (p_er(""), printf("'%c' isn't valid\n", map->map[i][j]), 1);
		else
			return (p_er(""), printf("'%c' isn't valid\n", map->map[i][j]), 1);
	}
}

void	get_check_map_map(t_map *map, int i, int j)
{
	if (map->map[i][j] != '0' && map->map[i][j] != 'N' && map->map[i][j] != 'S'
		&& map->map[i][j] != 'E' && map->map[i][j] != 'W')
	{
		if (check_map_map(map, i, j, 1) == 1)
			free_and_exit(map, 1);
	}
	else
	{
		if (check_map_map(map, i + 1, j, 0) == 1)
			free_and_exit(map, 1);
		if (check_map_map(map, i - 1, j, 0) == 1)
			free_and_exit(map, 1);
		if (check_map_map(map, i, j + 1, 0) == 1)
			free_and_exit(map, 1);
		if (check_map_map(map, i, j - 1, 0) == 1)
			free_and_exit(map, 1);
	}
}

void	check_map(t_map *map)
{
	int	i;
	int	j;
	int	count_player;

	i = 0;
	count_player = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
				count_player++;
			if (count_player > 1)
				return (p_er("Too many players\n"), free_and_exit(map, 1));
			get_check_map_map(map, i, j);
			j++;
		}
		i++;
	}
	if (count_player == 0)
		return (p_er("No player detected\n"), free_and_exit(map, 1));
}

//get map and datas from file and put it in map structure
void	find_start_map(t_map *map, char **temp, int i)
{
	char	**arr;
	int		j;

	while (i >= 0)
	{
		arr = ft_split(temp[i], " \n");
		if (ft_strlen(arr[0]) < 3 && (ft_strchr(temp[i], '/') != NULL
				|| ft_strchr(temp[i], ',') != NULL))
		{
			free_arr(arr);
			break ;
		}
		free_arr(arr);
		i--;
	}
	map->start_map = i;
	map->map = ft_calloc((arrlen(temp) - i + 1), sizeof(char *));
	map->data = ft_calloc((map->start_map + 2), sizeof(char *));
	j = 0;
	while (temp[++i])
	{
		map->map[j++] = ft_strdup(temp[i]);
		map->rows++;
	}
	i = -1;
	j = -1;
	while (i++ < map->start_map)
		map->data[++j] = ft_strdup(temp[i]);
}

void	print_datas_and_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->data[i])
	{
		printf("%s\n", map->data[i]);
		i++;
	}
	printf("------------------------------\n");
	i = 0;
	while (map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}

//read map and datas from file
int	get_map(t_map *map, char *path)
{
	char	**temp;
	char	*str;
	char	*file_temp;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (p_er("error reading the file\n"), 1);
	str = get_next_line(fd);
	file_temp = NULL;
	map->rows = 0;
	while (str)
	{
		file_temp = ft_straddstr(file_temp, str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	if (file_temp)
	{
		temp = ft_split(file_temp, "\n");
		find_start_map(map, temp, arrlen(temp) - 1);
		free_arr(temp);
		free(file_temp);
		print_datas_and_map(map);
		check_map(map);
	}
	return (0);
}
