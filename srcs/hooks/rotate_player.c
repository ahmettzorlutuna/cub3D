/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/28 16:09:44 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	rotate_vector(t_vec2 *vector, double cos, double sin)
{
	double	x;

	x = vector->x;
	vector->x = (vector->x * cos) - (vector->y * sin);
	vector->y = (x * sin) + (vector->y * cos);
}

static void	rotate_player(t_game *game, double rotate_angle)
{
	double	rot_cos;
	double	rot_sin;

	rot_cos = cos(rotate_angle);
	rot_sin = sin(rotate_angle);
	rotate_vector(&game->player.dir, rot_cos, rot_sin);
	rotate_vector(&game->player.plane, rot_cos, rot_sin);
}

void	turn_left(t_game *game)
{
	rotate_player(game, -ROTATE_SPEED);
}

void	turn_right(t_game *game)
{
	rotate_player(game, ROTATE_SPEED);
}
