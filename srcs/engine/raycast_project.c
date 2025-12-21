/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_project.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/11/10 13:57:28 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ray_project(t_game *game)
{
	if (!game->hit.hit)
		game->hit.perp_wall_dist = __DBL_MAX__;
	else if (game->hit.side == 0)
		game->hit.perp_wall_dist = (game->ray.map_x - game->player.pos.x
				+ (1 - game->ray.step_x) / 2.0) / game->ray.ray_dir_x;
	else
		game->hit.perp_wall_dist = (game->ray.map_y - game->player.pos.y
				+ (1 - game->ray.step_y) / 2.0) / game->ray.ray_dir_y;
	if (game->hit.perp_wall_dist <= 0.0)
		game->hit.perp_wall_dist = 0.0001;
	game->hit.line_h = (int)((double)WIN_H / game->hit.perp_wall_dist);
	game->hit.draw_start = -game->hit.line_h / 2 + WIN_H / 2;
	if (game->hit.draw_start < 0)
		game->hit.draw_start = 0;
	game->hit.draw_end = game->hit.line_h / 2 + WIN_H / 2;
	if (game->hit.draw_end >= WIN_H)
		game->hit.draw_end = WIN_H - 1;
}
