/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:44:27 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/30 19:41:22 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char			*pixel_addr;
	unsigned int	c;

	pixel_addr = game->mlx.addr + (y * game->mlx.line_len + x * (game->mlx.bpp
				/ 8));
	if (game->mlx.endian == 0)
		*(int *)pixel_addr = color;
	else
	{
		c = ((color & 0xFF) << 24)
			| ((color & 0xFF00) << 8)
			| ((color & 0xFF0000) >> 8)
			| ((color >> 24) & 0xFF);
		*(int *)pixel_addr = c;
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
