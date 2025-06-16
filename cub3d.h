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

# define NC "\e[0m"
# define RED "\e[31m"
# define BLUE "\e[34m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"

# define PLAYER_COLOR	0xEE0943
# define FLOOR_COLOR	0xFFFFFF
# define WALL_COLOR		0x403C37
# define EMPTY_COLOR	0x800080
# define OOB_COLOR		0xF0C807

# define KEY_LEFT		65361
# define KEY_RIGHT		65363
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_ESC		65307

# define WIDTH			1920
# define HEIGHT			1080
# define SIZE			12
# define FOV_DEGREE		66
# define PI				3.14159265359

# define FLOOR			0
# define WALL			1
# define EMPTY			2
# define OOB			3
# define FLOOR3D_PATH	"./assets/floor3d.xpm"
# define FLOOR_PATH		"./assets/floor.xpm"
# define WALL3D_PATH	"./assets/wall3d.xpm"
# define WALL_PATH		"./assets/wall.xpm"
# define EMPTY_PATH		"./assets/empty.xpm"
# define PLAYER_PATH	"./assets/player.xpm"
# define OOB_PATH		"./assets/oob.xpm"

# define X				1
# define Y				0

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
	double	dir[2];
	double	plane[2];
	double	ray_dir[2];
	int		grid_pos[2];
	double	delta_dist[2];
	int		step[2];
	double	side_dist[2];
	int		side_touch;
	int		x;
	double	raylength;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
}	t_camera;

typedef struct s_my_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_my_img;

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
	int			go_up;
	int			go_down;
	int			go_right;
	int			go_left;
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
	t_my_img	img;
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
double	get_rad(double degree);
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
void	init_direction_player(t_game *game);
/**========================================================================
 *!                               MAP
 *========================================================================**/
void	render_map(t_game *game);
int		render_map2d(t_game *game);
void	update_map2d(t_game *game);
void	fill_map(t_game *game, int x, int y);
void	draw_player(t_game *game, int x, int y, int color);
int		end_game(t_game *game);
int		destroy_all(int keysym, t_game *game);
/**========================================================================
 *!                            RAYCASTING
 *========================================================================**/
void	init_camera_angle(t_camera *camera, t_map *map);
void	update_camera_dir(t_camera *camera);
void	draw_ray(t_game *game, int color);
void	dda_algo(t_game *game, t_camera *camera, t_player *player, int x);
void	pix_put(t_my_img *img, int x, int y, int color);
void	draw_verline(t_my_img *img, t_camera *camera);

#endif
