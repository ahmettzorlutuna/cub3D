/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_project.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/29 04:10:05 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    ray_project(t_game *game, t_ray *ray, t_hit *h)
{
    if (!h->hit)
        h->perp_wall_dist = __DBL_MAX__; // duvara çarpmadıysa çok büyük bir mesafe
    else if (h->side == 0) // ışın dikey duvara çarptıysa
        h->perp_wall_dist = (ray->map_x - game->player.pos.x
                            + (1 - ray->step_x) / 2.0) / ray->ray_dir_x;
    else // ışın yatay duvara çarptıysa
        h->perp_wall_dist = (ray->map_y - game->player.pos.y
                            + (1 - ray->step_y) / 2.0) / ray->ray_dir_y;
    if (h->perp_wall_dist <= 0.0)
        h->perp_wall_dist = 0.0001;
    h->line_h = (int)((double)WIN_H / h->perp_wall_dist); // duvar yüksekliği uzaklık artarsa azalır
    h->draw_start = -h->line_h / 2 + WIN_H / 2; // ortanın yarım birim üstünden başla
    h->draw_end = h->line_h / 2 + WIN_H / 2; // ortanın yarım birim altına kadar çiz
}

void    ray_pick_color(t_hit *hit)
{
    int     base;

    base = 0x00AAFF; // mavi duvar
    if (hit->side == 1)
        base = (base >> 1) & 0x7F7F7F; // yatay duvarlar için koyu renk
    hit->color = base;
}
