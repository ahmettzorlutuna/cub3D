/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:44:27 by ekibar            #+#    #+#             */
/*   Updated: 2025/11/10 21:19:01 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_textures(t_game *game, char *path, int i)
{
	game->texture[i].img = mlx_xpm_file_to_image(
			game->mlx.mlx_ptr, path,
			&game->texture[i].width,
			&game->texture[i].height);
	if (!game->texture[i].img)
		exit_safe(game, "Texture yüklenemedi!", 1);
	game->texture[i].addr = mlx_get_data_addr(
			game->texture[i].img,
			&game->texture[i].bpp,
			&game->texture[i].line_len,
			&game->texture[i].endian);
	if (!game->texture[i].addr)
		exit_safe(game, "Texture yüklenemedi!", 1);
}
