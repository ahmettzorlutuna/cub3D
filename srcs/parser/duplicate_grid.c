/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_grid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:23:32 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/28 20:33:40 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**duplicate_grid(t_game *game, t_map *map)
{
	char	**map_copy;
	int		y;

	map_copy = malloc(sizeof(char *) * (map->height + 1));
	if (!map_copy)
		exit_safe(game, "Map copy malloc error", 1);
	y = 0;
	while (y < map->height)
	{
		map_copy[y] = ft_strdup(map->grid[y]);
		if (!map_copy[y])
		{
			while (y > 0)
				free(map_copy[--y]);
			free(map_copy);
			exit_safe(game, "Map line copy malloc error", 1);
		}
		y++;
	}
	map_copy[y] = NULL;
	return (map_copy);
}
