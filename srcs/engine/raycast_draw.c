/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/10/29 04:00:31 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    draw_world(t_game *game)
{
    int     x;
    t_ray   ray;
    t_hit   hit;

    x = 0;
    while (x < WIN_W)
    {
        ray_init(game, &ray, x);
        ray_step_init(game, &ray);
        ray_run_dda(game, &ray, &hit);
        ray_project(game, &ray, &hit);
        ray_pick_color(&hit);
        draw_vertical_line(game, x, &hit);
        x++;
    }
}
