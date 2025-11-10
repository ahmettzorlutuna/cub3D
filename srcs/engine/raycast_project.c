/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_project.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/11/10 13:57:28 by ekibar           ###   ########.fr       */
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

static int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;

	if (!texture || !texture->addr || texture->width <= 0 || texture->height <= 0)
		return (0xFFFFFF);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	pixel = texture->addr + (tex_y * texture->line_len + tex_x * (texture->bpp
				/ 8));
	return (*(unsigned int *)pixel);
}

static void	get_texture_coords(t_game *game, int tex_idx, int y)
{
	double		wall_hit_pos; // duvara çarpma pozisyonu
	double		texture_u; // dokunun x koordinatı
	int			d; // dokunun y koordinatı hesaplaması için yardımcı değişken

	if (game->hit.side == 0) // dikey duvara çarptıysa duvarın y koordinatını al
		wall_hit_pos = game->player.pos.y + game->hit.perp_wall_dist
			* game->ray.ray_dir_y;
	else // yatay duvara çarptıysa duvarın x koordinatını al
		wall_hit_pos = game->player.pos.x + game->hit.perp_wall_dist
			* game->ray.ray_dir_x;
	texture_u = wall_hit_pos - floor(wall_hit_pos); // duvar üzerindeki kesirli kısmı al
	game->hit.tex_x = (int)(texture_u * (double)game->texture[tex_idx].width);
	if ((game->hit.side == 0 && game->ray.step_x < 0) || (game->hit.side == 1 && game->ray.step_y > 0))
		game->hit.tex_x = game->texture[tex_idx].width - game->hit.tex_x - 1;
	d = y * 256 - WIN_H * 128 + game->hit.line_h * 128;
	game->hit.tex_y = ((d * game->texture[tex_idx].height) / game->hit.line_h) / 256;
}

static int	sample_texture(t_game *game, int i, int y)
{
	if (game->texture == NULL || i < 0 || i > 3)
		exit_safe(game, "Error\nInvalid texture index in sample_texture\n", 1);
	if (game->hit.line_h <= 0)
		exit_safe(game, "Error\nInvalid line height in sample_texture\n", 1);
	get_texture_coords(game, i, y);
	return (get_texture_color(&game->texture[i], game->hit.tex_x,
			game->hit.tex_y));
}

void    ray_pick_color(t_game *game, int y)
{
    // side==0 → x-duvarı (dikey yüz); step_x>0 ise doğu (E), <0 ise batı (W)
    // side==1 → y-duvarı (yatay yüz); step_y>0 ise güney (S), <0 ise kuzey (N)
    if (game->hit.side == 0)
    {
        if (game->ray.step_x > 0) // E
            game->hit.color = sample_texture(game, TEX_EAST, y);
        else // W
            game->hit.color = sample_texture(game, TEX_WEST, y);
    }
    else
    {
        if (game->ray.step_y > 0) // S
            game->hit.color = sample_texture(game, TEX_SOUTH, y);
        else // N
            game->hit.color = sample_texture(game, TEX_NORTH, y);
    }
}
