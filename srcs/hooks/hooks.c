/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/26 19:32:38 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int exit_window(t_game *game)
{
    exit_safe(game, "Window closed\n", 0);
    return (0);
}

int key_press_handler(int keycode, t_game *game)
{
    if (keycode == 119) // w'ye bastığında
        game->input_w = 1;
    else if (keycode == 115) // s 
        game->input_s = 1;
    else if (keycode == 97)  // a 
        game->input_a = 1;
    else if (keycode == 100) // d
        game->input_d = 1;
    else if (keycode == 65363) // sağa dön
        game->input_right = 1;
    else if (keycode == 65361) // sola dön
        game->input_left = 1;
    else if (keycode == 65307) // ESC
        exit_window(game);
    return (0);
}

int key_release_handler(int keycode, t_game *game)
{
    if (keycode == 119) // w bırakıldığında
        game->input_w = 0;
    else if (keycode == 115) // s 
        game->input_s = 0;
    else if (keycode == 97)  // a
        game->input_a = 0;
    else if (keycode == 100) // d 
        game->input_d = 0;
    else if (keycode == 65363) // sağa dön
        game->input_right = 0;
    else if (keycode == 65361) // sola dön
        game->input_left = 0;
    return (0);
}

// alınan input durumuna göre oyuncunun pozisyonunu ve yönünü günceller.
void apply_input(t_game *game)
{
    if (game->input_w) // ileri git
        go_forward(game);
    if (game->input_s) // geri git
        go_down(game);
    if (game->input_a) // sola git
        go_left(game);
    if (game->input_d) // sağa git
        go_right(game);
    if (game->input_left) // sola dön
        turn_left(game);
    if (game->input_right) // sağa dön
        turn_right(game);
}

// klavye ve pencere olaylarını işlemek için MLX kütüphanesinin hook fonksiyonlarını ayarlar.
void hooks_handler(t_game *game)
{
    mlx_hook(game->mlx.win_ptr, 2, 1L<<0, key_press_handler, game);
    mlx_hook(game->mlx.win_ptr, 3, 1L<<1, key_release_handler, game);
    mlx_hook(game->mlx.win_ptr, 17, 0, exit_window, game);
    mlx_loop_hook(game->mlx.mlx_ptr, game_loop, game);
}
