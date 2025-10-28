/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/26 19:32:38 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	rotate_vector(t_vec2 *vector, double cos, double sin)
{
	double  x;

	x = vector->x;
	vector->x = (vector->x * cos) - (vector->y * sin);
	vector->y = (x * sin) + (vector->y * cos);
}

static void rotate_player(t_game *game, double rotate_angle)
{
	double	rot_cos;
	double	rot_sin;

	rot_cos = cos(rotate_angle);
	rot_sin = sin(rotate_angle);
    printf("önce : dir[%f][%f] - plane[%f][%f]\n", game->player.dir.x ,game->player.dir.y, game->player.plane.x, game->player.plane.y);
	rotate_vector(&game->player.dir, rot_cos, rot_sin);
	rotate_vector(&game->player.plane, rot_cos, rot_sin);
    printf("sonra : dir[%f][%f] - plane[%f][%f]\n", game->player.dir.x, game->player.dir.y, game->player.plane.x, game->player.plane.y);
}

void    turn_left(t_game *game)
{
    rotate_player(game, -ROTATE_SPEED);
}

void    turn_right(t_game *game)
{
    rotate_player(game, ROTATE_SPEED);
}

void    setup_player_vectors(t_game *game)
{
    if (game->player.current_direction == 'N')
    {
        game->player.dir.x = 0;
        game->player.dir.y = -1;
        game->player.plane.x = FOV;
        game->player.plane.y = 0;
    }
    else if (game->player.current_direction == 'S')
    {
        game->player.dir.x = 0;
        game->player.dir.y = 1;
        game->player.plane.x = -FOV;
        game->player.plane.y = 0;
    }
    if (game->player.current_direction == 'W')
    {
        game->player.dir.x = -1;
        game->player.dir.y = 0;
        game->player.plane.x = 0;
        game->player.plane.y = -FOV;
    }
    if (game->player.current_direction == 'E')
    {
        game->player.dir.x = 1;
        game->player.dir.y = 0;
        game->player.plane.x = 0;
        game->player.plane.y = FOV;
    }
}
