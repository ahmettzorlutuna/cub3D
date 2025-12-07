/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_player_vectors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:18:25 by azorlutu          #+#    #+#             */
/*   Updated: 2025/11/12 20:18:25 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_player_north(t_game *game)
{
	game->player.dir.x = 0;
	game->player.dir.y = -1;
	game->player.plane.x = FOV;
	game->player.plane.y = 0;
}

void	set_player_south(t_game *game)
{
	game->player.dir.x = 0;
	game->player.dir.y = 1;
	game->player.plane.x = -FOV;
	game->player.plane.y = 0;
}

void	set_player_west(t_game *game)
{
	game->player.dir.x = -1;
	game->player.dir.y = 0;
	game->player.plane.x = 0;
	game->player.plane.y = -FOV;
}

void	set_player_east(t_game *game)
{
	game->player.dir.x = 1;
	game->player.dir.y = 0;
	game->player.plane.x = 0;
	game->player.plane.y = FOV;
}

void	setup_player_vectors(t_game *game)
{
	if (game->player.current_direction == 'N')
		set_player_north(game);
	else if (game->player.current_direction == 'S')
		set_player_south(game);
	else if (game->player.current_direction == 'W')
		set_player_west(game);
	else if (game->player.current_direction == 'E')
		set_player_east(game);
}
