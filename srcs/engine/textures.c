/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:44:27 by ekibar            #+#    #+#             */
/*   Updated: 2025/11/10 21:19:01 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_textures(t_game *game, char *path, int i)
{
	game->texture[i].img = mlx_xpm_file_to_image(
			game->mlx.mlx_ptr, path,
			&game->texture[i].width,
			&game->texture[i].height);
	if (!game->texture[i].img)
		exit_safe(game, "Texture yüklenemedi!", 1);
	game->texture[i].addr = mlx_get_data_addr(
			game->texture[i].img,
			&game->texture[i].bpp,
			&game->texture[i].line_len,
			&game->texture[i].endian);
	if (!game->texture[i].addr)
		exit_safe(game, "Texture yüklenemedi!", 1);
}

static	int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;

	if (!texture || !texture->addr || texture->width <= 0
		|| texture->height <= 0)
		return (0xFFFFFF);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	pixel = texture->addr + (tex_y * texture->line_len
			+ tex_x * (texture->bpp / 8));
	return (*(unsigned int *)pixel);
}

static	void	get_texture_coords(t_game *game, int tex_idx, int y)
{
	double	wall_hit_pos;
	double	texture_u;
	int		d;

	if (game->hit.side == 0)
		wall_hit_pos = game->player.pos.y
			+ game->hit.perp_wall_dist * game->ray.ray_dir_y;
	else
		wall_hit_pos = game->player.pos.x
			+ game->hit.perp_wall_dist * game->ray.ray_dir_x;
	texture_u = wall_hit_pos - floor(wall_hit_pos);
	game->hit.tex_x = (int)(texture_u * (double)game->texture[tex_idx].width);
	if ((game->hit.side == 0 && game->ray.step_x < 0)
		|| (game->hit.side == 1 && game->ray.step_y > 0))
		game->hit.tex_x = game->texture[tex_idx].width - game->hit.tex_x - 1;
	d = y * 256 - WIN_H * 128 + game->hit.line_h * 128;
	game->hit.tex_y = ((d * game->texture[tex_idx].height)
			/ game->hit.line_h) / 256;
}

static	int	sample_texture(t_game *game, int i, int y)
{
	if (game->texture == NULL || i < 0 || i > 3)
		exit_safe(game, "Error\nInvalid texture index in sample_texture\n", 1);
	if (game->hit.line_h <= 0)
		exit_safe(game, "Error\nInvalid line height in sample_texture\n", 1);
	get_texture_coords(game, i, y);
	return (get_texture_color(&game->texture[i], game->hit.tex_x,
			game->hit.tex_y));
}

void	ray_pick_color(t_game *game, int y)
{
	if (game->hit.side == 0)
	{
		if (game->ray.step_x > 0)
			game->hit.color = sample_texture(game, TEX_EAST, y);
		else
			game->hit.color = sample_texture(game, TEX_WEST, y);
	}
	else
	{
		if (game->ray.step_y > 0)
			game->hit.color = sample_texture(game, TEX_SOUTH, y);
		else
			game->hit.color = sample_texture(game, TEX_NORTH, y);
	}
}
