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

static void	exit_with_message(char *str, int exit_no)
{
	if (exit_no == 1)
		print_error_and_exit(str);
	else if (exit_no == 0)
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
		exit(exit_no);
	}
}

void	exit_safe(t_game *game, char *str, int exit_no)
{
	free_textures_and_images(game);
	free_map_paths_and_grid(game);
	free_mlx_and_window(game);
	exit_with_message(str, exit_no);
}

void	print_error_and_exit(char *message)
{
	ft_putstr_fd("Error..: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
