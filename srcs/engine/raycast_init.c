/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/29 00:48:05 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    ray_step_init(t_game *game, t_ray *ray)
{
    if (ray->ray_dir_x < 0.0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (game->player.pos.x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos.x) * ray->delta_dist_x;
    }
    if (ray->ray_dir_y < 0.0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->player.pos.y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos.y) * ray->delta_dist_y;
    }
}

void    ray_init(t_game *game, t_ray *ray, int x)
{
    ray->camera_x = 2.0 * x / (double)WIN_W - 1.0;
    ray->ray_dir_x = game->player.dir.x + game->player.plane.x * ray->camera_x;
    ray->ray_dir_y = game->player.dir.y + game->player.plane.y * ray->camera_x;
    ray->map_x = (int)game->player.pos.x;
    ray->map_y = (int)game->player.pos.y;
    if (ray->ray_dir_x == 0.0)
        ray->delta_dist_x = __DBL_MAX__;
    else
        ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
    if (ray->ray_dir_y == 0.0)
        ray->delta_dist_y = __DBL_MAX__;
    else
        ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}
