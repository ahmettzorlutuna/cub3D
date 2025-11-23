/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/30 15:56:57 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ray_step_init(t_game *game)
{
	if (game->ray.ray_dir_x < 0.0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist_x = (game->player.pos.x
				- game->ray.map_x) * game->ray.delta_dist_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist_x = (game->ray.map_x + 1.0
				- game->player.pos.x) * game->ray.delta_dist_x;
	}
	if (game->ray.ray_dir_y < 0.0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist_y = (game->player.pos.y
				- game->ray.map_y) * game->ray.delta_dist_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist_y = (game->ray.map_y + 1.0
				- game->player.pos.y) * game->ray.delta_dist_y;
	}
}

void	ray_init(t_game *game, int x)
{
	game->ray.camera_x = 2.0 * x / (double)WIN_W - 1.0;
	game->ray.ray_dir_x = game->player.dir.x
		+ game->player.plane.x * game->ray.camera_x;
	game->ray.ray_dir_y = game->player.dir.y
		+ game->player.plane.y * game->ray.camera_x;
	game->ray.map_x = (int)game->player.pos.x;
	game->ray.map_y = (int)game->player.pos.y;
	if (game->ray.ray_dir_x == 0.0)
		game->ray.delta_dist_x = __DBL_MAX__;
	else
		game->ray.delta_dist_x = fabs(1.0 / game->ray.ray_dir_x);
	if (game->ray.ray_dir_y == 0.0)
		game->ray.delta_dist_y = __DBL_MAX__;
	else
		game->ray.delta_dist_y = fabs(1.0 / game->ray.ray_dir_y);
}
