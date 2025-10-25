#ifndef CUB3D_H
# define CUB3D_H

#include "../lib/libft/libft.h"
#include "../srcs/parser/gnl/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

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
}	t_map;

typedef struct s_game
{
	t_mlx		mlx;
	t_player	player;
	t_map		map;
}	t_game;

void init_game(t_game *game);
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
void	print_error_and_exit(char *message);

# endif