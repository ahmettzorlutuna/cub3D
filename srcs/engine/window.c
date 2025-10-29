/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/28 15:50:08 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	create_window(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
		exit_safe(game, "Mlx_init failed!", 1);
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, WIN_W, WIN_H,
			"cub3D");
	if (!game->mlx.win_ptr)
		exit_safe(game, "Failed to create window!", 1);
	game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr, WIN_W, WIN_H);
	if (!game->mlx.img_ptr)
		exit_safe(game, "Failed to create image!", 1);
	game->mlx.addr = mlx_get_data_addr(game->mlx.img_ptr, &game->mlx.bpp,
			&game->mlx.line_len, &game->mlx.endian);
	if (!game->mlx.addr)
		exit_safe(game, "Failed to get image data address\n", 1);
	hooks_handler(game);
	mlx_loop(game->mlx.mlx_ptr);
}
