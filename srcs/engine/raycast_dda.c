/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/30 15:59:24 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	int	in_bounds(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map.height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(game->map.grid[y]))
		return (0);
	return (1);
}

void	ray_run_dda(t_game *game)
{
	game->hit.hit = 0;
	while (!game->hit.hit)
	{
		if (game->ray.side_dist_x < game->ray.side_dist_y)
		{
			game->ray.side_dist_x += game->ray.delta_dist_x;
			game->ray.map_x += game->ray.step_x;
			game->hit.side = 0;
		}
		else
		{
			game->ray.side_dist_y += game->ray.delta_dist_y;
			game->ray.map_y += game->ray.step_y;
			game->hit.side = 1;
		}
		if (!in_bounds(game, game->ray.map_x, game->ray.map_y))
			break ;
		if (game->map.grid[game->ray.map_y][game->ray.map_x] == '1')
			game->hit.hit = 1;
	}
}
