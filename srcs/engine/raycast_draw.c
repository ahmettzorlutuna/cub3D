/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/30 20:17:23 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_world(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_W)
	{
		ray_init(game, x);
		ray_step_init(game);
		ray_run_dda(game);
		ray_project(game);
		y = game->hit.draw_start;
		while (y < game->hit.draw_end)
		{
			ray_pick_color(game, y);
			put_pixel(game, x, y, game->hit.color);
			y++;
		}
		x++;
	}
}
