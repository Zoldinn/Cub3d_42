#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"

# define RED			"\e[31m"
# define NC				"\e[0m"
# define PLAYER_COLOR	0xEE0943
# define FLOOR_COLOR	0xFFFFFF
# define WALL_COLOR		0x403C37

# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_ESC		65307

# define SIZE			24
# define FOV_DEGREE		66
# define PI				3.14159265359

# define FLOOR			0
# define WALL			1
# define EMPTY			2
# define OOB			3
# define FLOOR_PATH		"./assets/floor.xpm"
# define WALL_PATH		"./assets/wall.xpm"
# define EMPTY_PATH		"./assets/empty.xpm"
# define PLAYER_PATH	"./assets/player.xpm"
# define OOB_PATH		"./assets/oob.xpm"

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

typedef struct s_camera
{
	double	angle_rad;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_camera;


typedef struct s_texture
{
	void	*img;
	char	*path;
}	t_texture;

typedef struct s_player
{
	t_texture	texture;
	double		pos_x;
	double		pos_y;
	int			neg_dir;
	t_camera	camera;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_map		map;
	int			**grid;
	t_texture	txt[4];
	t_player	player;
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
int		is_charset(char c, char *charset);
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
/**========================================================================
 *!                               MAP
 *========================================================================**/
int		render_map2D(t_game *game);
void	update_map2D(t_game *game);
void	fill_map(t_game *game, int x, int y);
void	draw_square(t_game *game, int color);
int		end_game(t_game *game);
int		destroy_all(int keysym, t_game *game);

#endif
