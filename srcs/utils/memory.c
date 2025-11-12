/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 22:28:52 by azorlutu          #+#    #+#             */
/*   Updated: 2025/11/10 21:23:53 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	cleanup_textures_and_images(t_game *game)
{
	if (game->texture && game->mlx.mlx_ptr)
	{
		if (game->texture[0].img)
			mlx_destroy_image(game->mlx.mlx_ptr, game->texture[0].img);
		if (game->texture[1].img)
			mlx_destroy_image(game->mlx.mlx_ptr, game->texture[1].img);
		if (game->texture[2].img)
			mlx_destroy_image(game->mlx.mlx_ptr, game->texture[2].img);
		if (game->texture[3].img)
			mlx_destroy_image(game->mlx.mlx_ptr, game->texture[3].img);
	}
	if (game->texture)
		free(game->texture);
}

static void	cleanup_map_paths_and_grid(t_game *game)
{
	if (game->map.north_texture_path)
		free(game->map.north_texture_path);
	if (game->map.south_texture_path)
		free(game->map.south_texture_path);
	if (game->map.east_texture_path)
		free(game->map.east_texture_path);
	if (game->map.west_texture_path)
		free(game->map.west_texture_path);
	if (game->map.grid)
		free_grid(game->map.grid);
}

static void	cleanup_mlx_and_window(t_game *game)
{
	if (game->mlx.img_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
	if (game->mlx.win_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	if (game->mlx.mlx_ptr)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
	}
}

void	cleanup(t_game *game)
{
	cleanup_textures_and_images(game);
	cleanup_map_paths_and_grid(game);
	cleanup_mlx_and_window(game);
}

void	free_string_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
