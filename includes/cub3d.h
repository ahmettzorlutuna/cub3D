#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include "../srcs/parser/gnl/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_ray
{
    double  camera_x;
    double  ray_dir_x;
    double  ray_dir_y;
    int     map_x;
    int     map_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    int     step_x;
    int     step_y;
}   t_ray;

typedef struct s_hit
{
    int     hit;
    int     side;
    double  perp_wall_dist;
    int     line_h;
    int     draw_start;
    int     draw_end;
    int     color;
}   t_hit;

typedef struct s_vec2
{
	double		x;
	double		y;
}				t_vec2;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_mlx;

typedef struct s_player
{
	t_vec2		pos;
	t_vec2		dir;
	t_vec2		plane;
	char		current_direction;
}				t_player;

typedef struct s_input
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_input;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	char		*north_texture_path;
	char		*south_texture_path;
	char		*west_texture_path;
	char		*east_texture_path;
	int			floor_color;
	int			ceiling_color;
	t_list		*line_list;
	int			is_map_started;
}				t_map;

typedef struct s_game
{
	t_mlx		mlx;
	t_player	player;
	t_map		map;
	t_input		input;
}				t_game;

# define MOVE_SPEED 0.08
# define ROTATE_SPEED 0.06
# define PLAYER_MARGIN 0.20
# define FOV 0.66
# define WIN_W 1024
# define WIN_H 768

/**
 * HOOKS
 */
void			go_forward(t_game *game);
void			go_down(t_game *game);
void			go_right(t_game *game);
void			go_left(t_game *game);
void			turn_right(t_game *game);
void			turn_left(t_game *game);
void			apply_input(t_game *game);
int				is_walkable(t_map *map, int row, int col);
void			setup_player_vectors(t_game *game);

/**
 * ENGINE
 */
void			create_window(t_game *game);
void			init_game(t_game *game);
void			exit_safe(t_game *game, char *str, int exit_no);
int				exit_window(t_game *game);
void			hooks_handler(t_game *game);
int				game_loop(void *game);
void			draw_world(t_game *game);
void			draw_vertical_line(t_game *game, int x, t_hit *hit);
void			ray_run_dda(t_game *game, t_ray *ray, t_hit *h);
void    		ray_step_init(t_game *game, t_ray *ray);
void    		ray_init(t_game *game, t_ray *ray, int x);
void    		ray_pick_color(t_hit *hit);
void    		ray_project(t_game *game, t_ray *ray, t_hit *h);


/**
 * PARSER
 */
void			validate_arguments(int argc, char **argv);
void			parse_map_lines(char *file_name, t_game *game);
void			parse_color(t_game *game, int *target_color, char **tokens);
int				is_digit_string(char *str);
void			free_string_array(char **array);
char			*create_map_line_copy(char *line);
void			handle_map_line(t_game *game, char *line, char **tokens,
					char *trimmed_line);
void			finalize_map_grid(t_map *map);
void			validate_map_content(t_game *game);
char			**duplicate_grid(t_map *map);
void			free_grid(char **grid);
void			flood_fill(char **map_copy, int height, int x, int y);

/**
 * ERROR
 */
void			print_error_and_exit(char *message);

#endif