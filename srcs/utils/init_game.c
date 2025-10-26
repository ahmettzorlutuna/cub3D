/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:45:56 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/19 22:45:57 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_game(t_game *game)
{
    ft_memset(game, 0, sizeof(t_game));
    game->map.floor_color = -1;
    game->map.ceiling_color = -1;
    game->map.is_map_started = -1;
}

