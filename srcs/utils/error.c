/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 23:21:53 by azorlutu          #+#    #+#             */
/*   Updated: 2025/11/10 21:21:18 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_safe(t_game *game, char *str, int exit_no)
{
	if (game->texture && game->mlx.mlx_ptr)
	{
		if (game->texture[0].img)
			mlx_destroy_image(game->mlx.mlx_ptr, game->texture[0].img);
		if (game->texture[1].img)
			mlx_destroy_image(game->mlx.mlx_ptr, game->texture[1].img);
		if (game->texture[2].img)
			mlx_destroy_image(game->mlx.mlx_ptr, game->texture[2].img);
		if (game->texture[3].img)
			mlx_destroy_image(game->mlx.mlx_ptr, game->texture[3].img);
	}
	if (game->texture)
		free(game->texture);
	if (game->map.north_texture_path)
		free(game->map.north_texture_path);
	if (game->map.south_texture_path)
		free(game->map.south_texture_path);
	if (game->map.east_texture_path)
		free(game->map.east_texture_path);
	if (game->map.west_texture_path)
		free(game->map.west_texture_path);
	if (game->map.grid)
		free_grid(game->map.grid);
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

void	print_error_and_exit(char *message)
{
	ft_putstr_fd("Error..: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
