/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/28 20:39:10 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	move_player(t_game *game, double dx, double dy)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = game->player.pos.x + dx;
	new_y = game->player.pos.y + dy;
	if (dx > 0)
		map_x = (int)(new_x + PLAYER_MARGIN);
	else
		map_x = (int)(new_x - PLAYER_MARGIN);
	map_y = (int)(game->player.pos.y);
	if (is_walkable(&game->map, map_y, map_x))
		game->player.pos.x = new_x;
	map_x = (int)(game->player.pos.x);
	if (dy > 0)
		map_y = (int)(new_y + PLAYER_MARGIN);
	else
		map_y = (int)(new_y - PLAYER_MARGIN);
	if (is_walkable(&game->map, map_y, map_x))
		game->player.pos.y = new_y;
}

void	go_forward(t_game *game)
{
	move_player(game, game->player.dir.x * MOVE_SPEED, game->player.dir.y
		* MOVE_SPEED);
}

void	go_down(t_game *game)
{
	move_player(game, -game->player.dir.x * MOVE_SPEED, -game->player.dir.y
		* MOVE_SPEED);
}

void	go_left(t_game *game)
{
	move_player(game, game->player.dir.y * MOVE_SPEED, -game->player.dir.x
		* MOVE_SPEED);
}

void	go_right(t_game *game)
{
	move_player(game, -game->player.dir.y * MOVE_SPEED, game->player.dir.x
		* MOVE_SPEED);
}
