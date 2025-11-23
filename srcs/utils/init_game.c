/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:45:56 by azorlutu          #+#    #+#             */
/*   Updated: 2025/11/10 13:44:59 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_game(t_game *game)
{
	game->texture = malloc(sizeof(t_texture) * 4);
	if (game->texture == NULL)
		exit_safe(game, "Failed to allocate memory for textures", 1);
	ft_memset(game->texture, 0, sizeof(t_texture) * 4);
	game->map.floor_color = -1;
	game->map.ceiling_color = -1;
	game->map.is_map_started = -1;
}
