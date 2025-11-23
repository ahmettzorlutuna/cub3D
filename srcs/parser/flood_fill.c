/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:26:51 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/25 19:26:52 by azorlutu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	flood_fill(t_game *game, char **map_copy, int x, int y)
{
	if (y < 0 || y >= game->map.height || map_copy[y] == NULL)
	{
		free_grid(map_copy);
		exit_safe(game, "Map open vertically", 1);
	}
	if (x < 0 || x >= (int)ft_strlen(map_copy[y]))
	{
		free_grid(map_copy);
		exit_safe(game, "Map open horizontally", 1);
	}
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'F')
		return ;
	if (map_copy[y][x] == ' ')
	{
		free_grid(map_copy);
		exit_safe(game, "There should be no gaps in the map!", 1);
	}
	if (ft_strchr("0NSEW", map_copy[y][x]))
		map_copy[y][x] = 'F';
	flood_fill(game, map_copy, x, y + 1);
	flood_fill(game, map_copy, x, y - 1);
	flood_fill(game, map_copy, x + 1, y);
	flood_fill(game, map_copy, x - 1, y);
}
