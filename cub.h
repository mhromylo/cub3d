#ifndef CUB_H
# define CUB_H

# define S_W	1024
# define S_H	800
# define ROTATION_SPEED	0.02
# define PLAYER_SPEED	0.02
# define M_PI	3.14159265358979323846
# define KEY_W	'w'
# define KEY_A	'a'
# define KEY_S	's'
# define KEY_D	'd'
# define KEY_ESC	65307
# define KEY_LEFT	65361
# define KEY_RIGHT	65363

# include <stdlib.h>
# include <math.h>
# include <X11/keysym.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "minilibx_opengl_20191021/mlx_opengl.h"
# include "minilibx_mms_20200219/mlx.h"
# include "gnl/get_next_line.h"

typedef struct s_raycast
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	dir_x;
	double	dir_y;
	double	view_x;
	double	view_y;
	int		map_x;
	int		map_y;
	double	ddx;
	double	ddy;
	double	step_x;
	double	step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		hit;
	int		side;
	double	wall_dist;
	double	texture_pos;
	double	texture_step;
	double	texture_y;
	double	texture_x;
	int		color;
	int		wall_type;
	int		draw_start;
	int		draw_end;
	int		line_h;
}				t_raycast;

typedef struct	s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}				t_imag;

typedef struct s_wall
{
	t_imag	*img;
	int		width;
	int		height;
}				t_wall;

typedef struct s_index
{
	int	north;
	int	south;
	int	west;
	int	east;
	int	floor;
	int	ceiling;
}				t_index;

typedef struct s_game
{
	int				map_height;
	int				map_length;
	double			player_pos_x;
	double			player_pos_y;
	char			**map_data;
	void			*mlx;
	void			*win;
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	char			*floor;
	char			*ceiling;
	char			direction;
	unsigned int	floor_bit;
	unsigned int	ceiling_bit;
	char			**map;
	char			*l_el;
	int				player_index;
	int				x;
	int				y;
	int				key_w;
	int				key_s;
	int				key_d;
	int				key_a;
	int				key_esc;
	int				key_right;
	int				key_left;
	t_raycast		*raycast;
	t_imag			img;
	t_index			s_index;
	t_wall			wall[4];
}	t_game;

int				close_game(t_game *game);
void			map_load(t_game *game, char *map);
void			map_fix(t_game *game);
void			last_element(t_game *game);
int				error_string(t_game *game);
void			init_player(t_game *game, int x, int y);
int				error_symbols(t_game *game);
int				error_corners(t_game *game);
int				check_char(char map, int i);
int				map_check(t_game *game);
int				error_walls_helper(t_game *game, size_t x, int y);
void			map_alloc(t_game *game);
char			*path_texture(t_game *game, char *str, int len);
void			arr_str_free(char **arr);
char			*ft_strdupn(const char *s1);
unsigned int	color_handle(char	*color_string);
char			*line_with_path(t_game *game, char *str, int len);
void			texture_load(t_game *game, char *path, int i);
char			**map_create(t_game *game);
void			map_maker(t_game *game, char *str);
void			init_facing_direction(t_game *game);
void			ceiling_floor(t_game *game);
void			walltype_detection(t_raycast *rc);
void			texture_assign(t_game *game, t_raycast *rc);
void			put_pixel(t_imag *img, int x, int y, int color);
unsigned int	get_pixel(t_imag *img, int x, int y);
void			draw_walls(t_game *game, t_raycast *rc, int x, int y);
void			raycast(t_game *game, t_raycast *rc);
void			front_move(t_game *game);
void			back_move(t_game *game);
void			left_move(t_game *game);
void			right_move(t_game *game);
void			rotate_left(t_game *game, double old_direction_x, double old_plane_x);
void			rotate_right(t_game *game, double old_direction_x, double old_plane_x);
int				draw_world(t_game *game);
int				key_press(int key, t_game *game);
int				key_release(int key, t_game *game);
int				keys_execute(t_game *game);
void 			cleanup(t_game *game);
int				close_after_mlx(t_game *game);

#endif