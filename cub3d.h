#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"

typedef struct s_map
{
	char	**data;
	char	**map;
	int		rows;
	int		start_map;
	char	**txt;
}	t_map;

/**========================================================================
 *!                           CHECK ERRORS
 *========================================================================**/
int		check_extension(char *file_name, char *ext);
/**========================================================================
 *!                              PARSING
 *========================================================================**/
int		get_map(t_map *map, char *path);
char	*get_next_line(int fd);
int		check_file(char *path, t_map *map);
/**========================================================================
 *!                               UTILS
 *========================================================================**/
char	*ft_straddstr(char *s1, char *s2);
char	*get_next_line(int fd);
char	*get_rgb(char *id, t_map *map);
/**========================================================================
 *!                               FREE
 *========================================================================**/
void	free_arr(char **arr);
void	free_and_exit(t_map *map, int code);
void	free_map(t_map *map);
int		arrlen(char **arr);
int		ft_check_atoi(const char *nptr);
int		ft_cmpstr(char *s1, char *s2);
void	p_er(char *str);

#endif
