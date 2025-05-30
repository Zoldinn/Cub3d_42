#include "../cub3d.h"

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
