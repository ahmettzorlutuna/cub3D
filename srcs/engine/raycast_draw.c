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

static	void	draw_column(t_game *game, int x)
{
	int	y;
	int	draw_start;
	int	draw_end;

	ray_init(game, x);
	ray_step_init(game);
	ray_run_dda(game);
	ray_project(game);
	draw_start = game->hit.draw_start;
	draw_end = game->hit.draw_end;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIN_H)
		draw_end = WIN_H - 1;
	y = draw_start;
	while (y < draw_end)
	{
		ray_pick_color(game, y);
		put_pixel(game, x, y, game->hit.color);
		y++;
	}
}

void	draw_world(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		draw_column(game, x);
		x++;
	}
}
