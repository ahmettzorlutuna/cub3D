#ifndef CUB3D_H
# define CUB3D_H

#include "../lib/libft/libft.h"
#include "../srcs/parser/gnl/get_next_line.h"
#include "../lib/minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <math.h>

typedef struct s_vec2
{
    double	x;
    double	y;
} t_vec2;

typedef struct s_mlx
{
    void	*mlx_ptr;
    void	*win_ptr;
    void	*img_ptr;
    char    *addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_mlx;

typedef struct s_player
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	plane;
	char	current_direction;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
	int		floor_color;
	int		ceiling_color;
	t_list	*line_list;
	int		is_map_started;
}	t_map;

typedef struct s_game
{
	t_mlx		mlx;
	t_player	player;
	t_map		map;
	/* input flags for KeyPress/KeyRelease */
	int         input_w;
	int         input_a;
	int         input_s;
	int         input_d;
	int         input_left;
	int         input_right;
}   t_game;

/* Input and movement constants */
#define MOVE_SPEED 0.08
#define ROT_SPEED  0.06
#define COLLIDE_RAD 0.20
#define WIN_W 1024
#define WIN_H 768

/* Functions to control input/movement */
void    apply_input(t_game *g);
int     is_walkable(t_map *map, int row, int col);
void    try_move(t_game *g, double dx, double dy);
void    rotate_player(t_game *g, double angle);

/**
 * ENGINE
 */
void	create_window(t_game *game);
void	init_game(t_game *game);
void	go_forward(t_game * game);
void	go_down(t_game * game);
void	go_right(t_game * game);
void	go_left(t_game * game);
void	turn_right(t_game * game);
void	turn_left(t_game * game);
int		exit_window(t_game *game);
int		handler(int code, t_game *game);
void	hooks_handler(t_game *game);

/**
 * PARSER
 */
void    validate_arguments(int argc, char **argv);
void	parse_map_lines(char *file_name, t_game *game);
void	parse_color(t_game *game, int *target_color, char **tokens);
int		is_digit_string(char *str);
void	free_string_array(char **array);
char	*create_map_line_copy(char *line);
void	handle_map_line(t_game *game, char *line, char **tokens, char *trimmed_line);
void	finalize_map_grid(t_map *map);
void	validate_map_content(t_game *game);
char	**duplicate_grid(t_map *map);
void	free_grid(char **grid);
void    flood_fill(char **map_copy, int height, int x, int y);

/**
 * ERROR
 */
void	print_and_exit(t_game *game, char *message, int exit_code);
void	free_safe(t_game *game);

# endif