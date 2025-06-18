#include "../../cub3d.h"

//compare 2 strings
//0 if same
//1 if different
int	ft_cmpstr(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) == ft_strlen(s2))
	{
		if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
			return (0);
	}
	return (1);
}

// -1 if arr == null
// else return the nb of stringss
int	arrlen(char **arr)
{
	int	i;

	if (arr == NULL)
		return (-1);
	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char	*get_rgb(char *id, t_map *map)
{
	int		i;
	char	*clean;
	char	*data;
	int		len;

	i = -1;
	while (map->txt[++i])
	{
		if (ft_strnstr(map->txt[i], id, ft_strlen(map->txt[i])) != NULL)
		{
			len = ft_strlen(map->txt[i]) - ft_strlen(id);
			clean = ft_strtrim(map->txt[i], " \t");
			data = ft_substr(clean, ft_strlen(id), len);
			free(clean);
			return (data);
		}
	}
	return (NULL);
}

int	is_charset(char c, char *charset)
{
	int	i;

	i = -1;
	if (!charset)
		return (0);
	while (charset[++i])
	{
		if (charset[i] == c)
			return (1);
	}
	return (0);
}

int	rgb_to_hex(char *rgb)
{
	char	**arr;
	int		res;

	arr = ft_split(rgb, ",");
	res = (ft_atoi(arr[0]) << 16) | (ft_atoi(arr[1]) << 8) | ft_atoi(arr[2]);
	free_arr(arr);
	return (res);
}
