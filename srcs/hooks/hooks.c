/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/28 20:38:00 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	exit_window(t_game *game)
{
	exit_safe(game, "", 0);
	return (0);
}

int	key_press_handler(int keycode, t_game *game)
{
	if (keycode == 119)
		game->input.w = 1;
	else if (keycode == 115)
		game->input.s = 1;
	else if (keycode == 97)
		game->input.a = 1;
	else if (keycode == 100)
		game->input.d = 1;
	else if (keycode == 65363)
		game->input.right = 1;
	else if (keycode == 65361)
		game->input.left = 1;
	else if (keycode == 65307)
		exit_window(game);
	return (0);
}

int	key_release_handler(int keycode, t_game *game)
{
	if (keycode == 119)
		game->input.w = 0;
	else if (keycode == 115)
		game->input.s = 0;
	else if (keycode == 97)
		game->input.a = 0;
	else if (keycode == 100)
		game->input.d = 0;
	else if (keycode == 65363)
		game->input.right = 0;
	else if (keycode == 65361)
		game->input.left = 0;
	return (0);
}

void	apply_input(t_game *game)
{
	if (game->input.w)
		go_forward(game);
	if (game->input.s)
		go_down(game);
	if (game->input.a)
		go_left(game);
	if (game->input.d)
		go_right(game);
	if (game->input.left)
		turn_left(game);
	if (game->input.right)
		turn_right(game);
}

void	hooks_handler(t_game *game)
{
	mlx_hook(game->mlx.win_ptr, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->mlx.win_ptr, 3, 1L << 1, key_release_handler, game);
	mlx_hook(game->mlx.win_ptr, 17, 0, exit_window, game);
	mlx_loop_hook(game->mlx.mlx_ptr, game_loop, game);
}
