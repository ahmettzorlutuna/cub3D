/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:44:27 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/29 04:04:53 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*pixel_addr;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	pixel_addr = game->mlx.addr + (y * game->mlx.line_len + x * (game->mlx.bpp
				/ 8));
	*(int *)pixel_addr = color;
}

void	draw_vertical_line(t_game *game, int x, t_hit *hit)
{
	int		y;

	if (x < 0 || x >= WIN_W) // sınırların dışındaysa
		return ;
	if (hit->draw_start < 0) // ekrandan taşarsa yukarı taşmayı kes
		hit->draw_start = 0;
	if (hit->draw_end >= WIN_H) // ekrandan taşarsa aşağı taşmayı kes
		hit->draw_end = WIN_H - 1;
	y = hit->draw_start; 
	while (y <= hit->draw_end)
	{
		put_pixel(game, x, y, hit->color);
		y++;
	}
}

static void	draw_background(t_game *game)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < WIN_H)
	{
		if (y < WIN_H / 2)
			color = game->map.ceiling_color;
		else
			color = game->map.floor_color;
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

int	game_loop(void *g)
{
	t_game	*game;

	game = (t_game *)g;
	apply_input(game);
	draw_background(game);
	draw_world(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->mlx.img_ptr, 0, 0);
	return (0);
}
