#include "../cub3d.h"

int	check_rgb_values(char *rgb[2])
{
	int		i;
	char	**values;
	int		j;
	int		value;

	i = -1;
	while (++i < 2)
	{
		values = ft_split(rgb[i], " ,");
		if (!values)
			return (p_er("Failed to split rgb values"), 1);
		j = 0;
		while (values[++j])
		{
			value = ft_check_atoi(values[j]);
			if (value < 0 || value > 255)
				return (p_er("RGB should be [0;255]"), free_arr(values), 1);
		}
		if (j != 4)
			return (p_er("RGB values should be 3 int"), free_arr(values), 1);
		free_arr(values);
	}
	return (0);
}

int	get_data(t_map *map, char **id, int i)
{
	int		j;
	char	**line;

	while (map->data[++i])
	{
		line = ft_split(map->data[i], " \n\t\0");
		if (!line)
			return (1);
		j = -1;
		while (id[++j])
		{
			if (ft_cmpstr(line[0], id[j]) == 0)
			{
				if (map->txt[j] == NULL)
					map->txt[j] = ft_strdup(line[1]);
				else
					return (p_er("multiple time a texture"), free_arr(line), 1);
				break ;
			}
		}
		if (ft_cmpstr(line[0], id[j]) != 0)
			return (p_er("there's something not required"), free_arr(line), 1);
		free_arr(line);
	}
	return (0);
}

char	**ids(void)
{
	char	**id;

	id = ft_calloc(sizeof(char *), 7);
	if (!id)
		return (NULL);
	id[0] = "NO";
	id[1] = "SO";
	id[2] = "WE";
	id[3] = "EA";
	id[4] = "F";
	id[5] = "C";
	return (id);
}

int	check_txt(t_map *map)
{
	int	i;
	// int	fd;

	if (map->txt == NULL)
		return (1);
	i = -1;
	while (++i < 4)
	{
		if (map->txt[i] && check_extension(map->txt[i], ".xpm") != 0)
			return (1);
		else if (map->txt[i] == NULL)
			return (1);
		// fd = open(map->txt[i], O_RDONLY);
		// if (fd <= 0)
		// 	return (p_er("failed openning a file"), 1);
		// close(fd);
	}
	return (0);
}

int	check_file(char *path, t_map *map)
{
	int		i;
	int		count;
	char	*rgb[2];
	char	**id;

	if (get_map(map, path) != 0 || map->data == NULL || map->map == NULL)
		return (p_er("Failed to get the file"), 1);
	map->txt = ft_calloc(sizeof(char *), 7);
	if (!map->txt)
		return (1);
	id = ids();
	if (get_data(map, id, -1) != 0)
		return (free(id), 1);
	free(id);
	i = -1;
	count = 0;
	while (map->txt[++i])
		count++;
	if (count != 6)
		return (p_er("there's something missing"), 1);
	rgb[0] = map->data[4];
	rgb[1] = map->data[5];
	if (check_rgb_values(rgb) != 0 || check_txt(map) != 0)
		return (1);
	return (0);
}
