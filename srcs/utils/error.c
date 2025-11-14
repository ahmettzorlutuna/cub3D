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
	if (exit_no == 0)
		exit(0);
	print_error_and_exit(str);
}

void	exit_safe(t_game *game, char *str, int exit_no)
{
	free_gnl_buffer();
	if (game != NULL)
	{
		free_parser_state(game);
		free_textures_and_images(game);
		free_map_paths_and_grid(game);
		free_mlx_and_window(game);
	}
	exit_with_message(str, exit_no);
}

void	print_error_and_exit(char *message)
{
	if (message != NULL && *message != '\0')
		ft_putstr_fd(message, 2);
	exit(1);
}
