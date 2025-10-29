/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/29 03:17:58 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int  in_bounds(t_game *game, int x, int y)
{
    if (y < 0 || y >= game->map.height)
        return (0);
    if (x < 0 || x >= (int)ft_strlen(game->map.grid[y]))
        return (0);
    return (1);
}

void    ray_run_dda(t_game *game, t_ray *ray, t_hit *h)
{
    h->hit = 0;
    while (!h->hit)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            h->side = 0; // ışın dikey çizgiden geçti
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            h->side = 1; // ışın yatay çizgiden geçti
        }
        if (!in_bounds(game, ray->map_x, ray->map_y))
            break;
        if (game->map.grid[ray->map_y][ray->map_x] == '1') // duvara çarptı
            h->hit = 1;
    }
}
