#include "../cub3d.h"

int	check_extension(char *file_name, char *ext)
{
	int	len;

	len = ft_strlen(file_name);
	if (len <= 4)
		return (p_er(""), printf("file type isn't %s\n", ext), 1);
	else if (file_name[len - 4] != ext[0]
		|| file_name[len - 3] != ext[1]
		|| file_name[len - 2] != ext[2]
		|| file_name[len - 1] != ext[3]
		|| file_name[len] != '\0')
		return (p_er(""), printf("file type isn't %s\n", ext), 1);
	return (0);
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

void	init_map(t_map *map)
{
	map->data = NULL;
	map->map = NULL;
	map->txt = NULL;
	map->rows = 0;
	map->lines_data = 0;
}

int	main(int argc, char **argv)
{
	t_map	map;

	init_map(&map);
	if (check_args(argc, argv) != 0)
		return (free_map(&map), 1);
	if (check_file(argv[1], &map) != 0)
		return (free_map(&map), 1);
	free_map(&map);
	return (printf("\e[32mParsing ok !\e[0m"), 0);
}
