/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 23:21:53 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/21 23:21:54 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_safe(t_game *game)
{
    if (game->mlx.img_ptr)
        mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
    if (game->mlx.win_ptr)
        mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
    if (game->mlx.mlx_ptr)
    {
        mlx_destroy_display(game->mlx.mlx_ptr);
        free(game->mlx.mlx_ptr);
    }
}

void print_and_exit(t_game *game, char *message, int exit_code)
{
    free_safe(game);
    if (exit_code == 1)
    {
        ft_putstr_fd("Error..: ", 2);
        ft_putstr_fd(message, 2);
        ft_putstr_fd("\n", 2);
    }
    else if (exit_code == 0)
    {
        ft_putstr_fd(message, 1);
        ft_putstr_fd("\n", 1);
    }
    exit(exit_code);
}