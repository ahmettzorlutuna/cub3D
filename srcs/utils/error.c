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

void	exit_safe(t_game *game, char *str, int exit_no)
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
    if (exit_no == 1)
        print_error_and_exit(str);
    else if (exit_no == 0)
    {
        ft_putstr_fd(str, 1);
        ft_putstr_fd("\n", 1);
        exit(exit_no);
    }
}

void print_error_and_exit(char *message)
{
    ft_putstr_fd("Error..: ", 2);
    ft_putstr_fd(message, 2);
    ft_putstr_fd("\n", 2);
    exit(1);
}