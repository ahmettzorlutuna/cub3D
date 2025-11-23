/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 22:28:52 by azorlutu          #+#    #+#             */
/*   Updated: 2025/11/10 21:23:53 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	destroy_texture_images(t_game *game)
{
	int	i;

	if (!game->texture || !game->mlx.mlx_ptr)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->texture[i].img)
		{
			mlx_destroy_image(game->mlx.mlx_ptr, game->texture[i].img);
			game->texture[i].img = NULL;
		}
		i++;
	}
}

void	free_textures_and_images_and_grid(t_game *game)
{
	if (!game || !game->texture)
		return ;
	if (game->map.grid)
	{
		free_grid(game->map.grid);
		game->map.grid = NULL;
	}
	destroy_texture_images(game);
	free(game->texture);
	game->texture = NULL;
}

void	free_map_paths(t_game *game)
{
	if (!game)
		return ;
	if (game->map.north_texture_path)
	{
		free(game->map.north_texture_path);
		game->map.north_texture_path = NULL;
	}
	if (game->map.south_texture_path)
	{
		free(game->map.south_texture_path);
		game->map.south_texture_path = NULL;
	}
	if (game->map.east_texture_path)
	{
		free(game->map.east_texture_path);
		game->map.east_texture_path = NULL;
	}
	if (game->map.west_texture_path)
	{
		free(game->map.west_texture_path);
		game->map.west_texture_path = NULL;
	}
}

void	free_mlx_and_window(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx.img_ptr && game->mlx.mlx_ptr)
	{
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
		game->mlx.img_ptr = NULL;
	}
	if (game->mlx.win_ptr && game->mlx.mlx_ptr)
	{
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
		game->mlx.win_ptr = NULL;
	}
	if (game->mlx.mlx_ptr)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
		game->mlx.mlx_ptr = NULL;
	}
}

void	cleanup(t_game *game)
{
	if (!game)
		return ;
	free_textures_and_images_and_grid(game);
	free_map_paths(game);
	free_mlx_and_window(game);
}
