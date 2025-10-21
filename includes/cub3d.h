#ifndef CUB3D_H
# define CUB3D_H

#include "../lib/libft/libft.h"
#include "./srcs/parser/gnl/get_next_line.h"
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
void	parse_mapfile(char *file_name, t_game *game);
/**
 * ERROR
 */
void	print_error_and_exit(char *message);

# endif