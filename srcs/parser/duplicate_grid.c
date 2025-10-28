/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_grid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:23:32 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/28 20:33:40 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char **duplicate_grid(t_map *map)
{
	char	**map_copy;
	int		y;
	
	map_copy = malloc(sizeof(char *) * (map->height + 1));
	if(!map_copy)
		print_error_and_exit("Map copy malloc error");
	y = 0;
	while (y < map->height)
	{
		map_copy[y] = ft_strdup(map->grid[y]);
		if (!map_copy[y])
		{
			while (y > 0)
				free(map_copy[--y]);
			free(map_copy);
			print_error_and_exit("Map line copy malloc error");
		}
		y++;
	}
	map_copy[y] = NULL;
	return(map_copy);
}
