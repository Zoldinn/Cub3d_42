#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdint.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"

# define TORCH1_PATH	"./textures/torch1.xpm"
# define TORCH2_PATH	"./textures/torch2.xpm"
# define TORCH3_PATH	"./textures/torch3.xpm"
# define TORCH4_PATH	"./textures/torch4.xpm"
# define TORCH5_PATH	"./textures/torch5.xpm"
# define TORCH6_PATH	"./textures/torch6.xpm"
# define TORCH7_PATH	"./textures/torch7.xpm"
# define TORCH8_PATH	"./textures/torch8.xpm"

# define NC "\e[0m"
# define RED "\e[31m"
# define BLUE "\e[34m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"

# define PLAYER_COLOR	0xEE0943
# define FLOOR_COLOR	0x96B4B2
# define WALL_COLOR		0x2D3949
# define EMPTY_COLOR	0x800080
# define OOB_COLOR		0xF0C807
# define DOOR_COLOR		0x8F521A

# define KEY_LEFT		65361
# define KEY_RIGHT		65363
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_ESC		65307

# define WIDTH			1920
# define HEIGHT			1080

# define SIZE			WIDTH / 160
# define FOV_DEGREE		66
# define PI				3.14159265359

# define SPEED			0.1f
# define WALL_N			0
# define WALL_S			1
# define WALL_W			2
# define WALL_E			3

# define X				1
# define Y				0

// "vertical" == a wall east or west
# define VERTICAL		0
// "horizontal" == a wall north or south
# define HORIZONTAL		1

# define WALL			0
# define TEX			1

typedef struct s_input
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_input;

typedef struct s_map
{
	char	**data;
	char	**map;
	char	**rgb;
	char	**txt;
	int		*door_pos_x;
	int		*door_pos_y;
	int		rows;
	int		col_max;
	int		lines_data;
	int		start_map;
	int		floor_color;
	int		ceil_color;
	int		nb_doors;
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
	double	raylen;
}	t_camera;

typedef struct s_my_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		color;
}	t_my_img;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	char	*path;
	int		width;
	int		height;
	int		bpp;
	int		endian;
	int		size_line;
}	t_texture;

typedef struct s_player
{
	t_texture	texture;
	double		pos_x;
	double		pos_y;
	t_camera	camera;
}	t_player;

typedef struct s_tex_mapping
{
	double		line_height;
	double		draw_start;
	double		draw_end;
	double		x[2];
	int			color;
	t_texture	*tex;
	double		step;
	double		y;
}	t_tex_mapping;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_input		input;
	t_map		map;
	t_player	player;
	t_texture	wall[4];
	t_texture	torch[8];
	t_my_img	screen_img;
}	t_game;

/**========================================================================
 *!                           CHECK ERRORS
 *========================================================================**/
int			check_extension(char *file_name, char *ext);
/**========================================================================
 *!                              PARSING
 *========================================================================**/
int			check_args(int argc, char **argv);
int			get_map(t_map *map, char *path);
char		*get_next_line(int fd);
int			check_file(char *path, t_map *map);
int			is_valid_letter_map(t_map *map, int i, int j);
/**========================================================================
 *!                               UTILS
 *========================================================================**/
char		*ft_straddstr(char *s1, char *s2);
char		*get_next_line(int fd);
void		print_datas_and_map(t_map *map);
void		find_start_map(t_map *map, int *i, char **temp);
void		find_end_map(t_map *map, int *i, char **temp);
void		check_empty_lines_map(t_map *map, char *file_temp);
char		*get_rgb(char *id, t_map *map);
int			is_charset(char c, char *charset);
double		get_rad(double degree);
int			rgb_to_hex(char *rgb);
/**========================================================================
 *!                               FREE
 *========================================================================**/
void		free_arr(char **arr);
void		free_and_exit(t_map *map, int code);
void		free_map(t_map *map);
void		free_walls_texture(t_game *game);
int			arrlen(char **arr);
int			ft_check_atoi(const char *nptr);
int			ft_cmpstr(char *s1, char *s2);
void		p_er(char *str);
/**========================================================================
 *!                          INIT AND CLOSE
 *========================================================================**/
void		init_map(t_map *map);
void		init_game(t_game *game);
void		init_texture(t_game *game);
void		init_pos_player(t_game *game);
void		init_img(t_my_img *img);
void		get_textures_wall(t_game *game);
/**========================================================================
 *!                               MAP
 *========================================================================**/
void		render_map(t_game *game);
int			render_map2d(t_game *game);
int			render_loop(t_game *game);
void		put_pixel(t_my_img *img, int x, int y, int color);
void		fill_map(t_game *game, int x, int y);
void		draw_square(t_my_img *img, double x, double y, int color);
int			end_game(t_game *game);
/**========================================================================
 *!                            RAYCASTING
 *========================================================================**/
void		init_camera_angle(t_camera *camera, t_map *map);
void		update_camera_dir(t_camera *camera);
void		draw_ray(t_game *game, int color);
void		dda_algo(t_game *game, t_camera *camera, t_player *player, int x);
void		put_pixel(t_my_img *img, int x, int y, int color);
void		draw_vertical_line(t_my_img *img, t_game *game, t_camera *camera);
void		raycasting(t_game *game, t_camera *camera);
int			get_tex_pixel_color(t_texture *tex, int x, int y);
t_texture	*get_wall_tex(t_game *game, t_camera *camera);
void		get_wall_x(t_game *game, t_tex_mapping *tex);
void		get_tex_x(t_camera *camera, t_tex_mapping *tex);
/**========================================================================
 *!                              PLAYER
 *========================================================================**/
void		move_player(int keysym, t_game *game);
void		draw_player(t_my_img *img, double x, double y, int color);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
void		render_torch(t_game *game);
void		draw_torch(t_game *game, t_texture *tex);
/**========================================================================
 *!                              CAMERA
 *========================================================================**/
void		move_camera(int keysym, t_game *game);

#endif
