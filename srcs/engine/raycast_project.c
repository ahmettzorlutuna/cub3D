/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_project.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/30 17:42:24 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    ray_project(t_game *game)
{
    if (!game->hit.hit)
        game->hit.perp_wall_dist = __DBL_MAX__; // duvara çarpmadıysa çok büyük bir mesafe
    else if (game->hit.side == 0) // ışın dikey duvara çarptıysa
        game->hit.perp_wall_dist = (game->ray.map_x - game->player.pos.x
                            + (1 - game->ray.step_x) / 2.0) / game->ray.ray_dir_x;
    else // ışın yatay duvara çarptıysa
        game->hit.perp_wall_dist = (game->ray.map_y - game->player.pos.y
                            + (1 - game->ray.step_y) / 2.0) / game->ray.ray_dir_y;
    if (game->hit.perp_wall_dist <= 0.0)
        game->hit.perp_wall_dist = 0.0001;
    game->hit.line_h = (int)((double)WIN_H / game->hit.perp_wall_dist); // duvar yüksekliği uzaklık artarsa azalır
    game->hit.draw_start = -game->hit.line_h / 2 + WIN_H / 2; // ortanın yarım birim üstünden başla
    game->hit.draw_end = game->hit.line_h / 2 + WIN_H / 2; // ortanın yarım birim altına kadar çiz
}

void    ray_pick_color(t_game *game, int x, int y)
{
    int     base;
    (void)x; // kullanılmayan parametre uyarısını önlemek için
    (void)y; // kullanılmayan parametre uyarısını önlemek için

    base = 0xFFFFFF; // beyaz varsayılan renk

    // side==0 → x-duvarı (dikey yüz); step_x>0 ise doğu (E), <0 ise batı (W)
    // side==1 → y-duvarı (yatay yüz); step_y>0 ise güney (S), <0 ise kuzey (N)
    if (game->hit.side == 0)
    {
        if (game->ray.step_x > 0) // E
        {
            // her pixele texture dosyama göre renk ataması
            

        }
        else // W
        {

        }
    }
    else
    {
        if (game->ray.step_y > 0) // S
        {

        }
        else // N
        {

        }
    }
    game->hit.color = base;
}
