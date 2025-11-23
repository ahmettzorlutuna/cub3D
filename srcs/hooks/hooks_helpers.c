/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/28 15:55:59 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_walkable(t_map *map, int row, int col)
{
	int		row_len;
	char	c;

	if (row < 0 || row >= map->height)
		return (0);
	row_len = (int)strlen(map->grid[row]);
	if (col < 0 || col >= row_len)
		return (0);
	c = map->grid[row][col];
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}
