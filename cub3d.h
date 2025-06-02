#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"

# define R					"\e[31m"
# define N					"\e[0m"
# define KEY_ESC			65307

# define FLOOR_PATH			"./assets/floor.xpm"
# define WALL_PATH			"./assets/wall.xpm"

typedef struct s_map
{
	char	**data;
	char	**map;
	int		rows;
	int		col_max;
	int		lines_data;
	int		start_map;
	char	**txt;
}	t_map;

typedef struct s_texture
{
	void	*img;
	char	*path;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_texture	floor;
	t_texture	wall;
}	t_game;

typedef enum e_id
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}	t_id;

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
void	print_datas_and_map(t_map *map);
void	find_start_map(t_map *map, int *i, char **temp);
void	find_end_map(t_map *map, int *i, char **temp);
void	check_empty_lines_map(t_map *map, char *file_temp);
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
/**========================================================================
 *!                          INIT AND CLOSE
 *========================================================================**/
void	init_map(t_map *map);
void	init_game(t_game *game);
void	init_texture(t_game *game);
int		render_map(t_game *game);
int		end_game(t_game *game);
int		destroy_all(int keysym, t_game *game);

#endif
