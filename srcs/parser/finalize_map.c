/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 21:10:36 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/23 21:10:36 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	void	check_map_chars_and_player(t_game *game, int *player_count)
{
	int		x;
	int		y;
	char	current_char;

	y = 0;
	*player_count = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x] != '\0')
		{
			current_char = game->map.grid[y][x];
			if (!ft_strchr("01NWSE ", current_char))
				exit_safe(game, "Invalid char found in the map", 1);
			if (ft_strchr("NWSE", current_char))
			{
				(*player_count)++;
				game->player.pos.x = (double)x + 0.5;
				game->player.pos.y = (double)y + 0.5;
				game->player.current_direction = current_char;
			}
			x++;
		}
		y++;
	}
}

void	validate_map_content(t_game *game)
{
	int		player_count;
	char	**map_copy;

	check_map_chars_and_player(game, &player_count);
	if (player_count != 1)
		exit_safe(game, "There should be 1 player on the map.", 1);
	map_copy = duplicate_grid(game, &game->map);
	flood_fill(game, map_copy,
		(int)game->player.pos.x, (int)game->player.pos.y);
	free_grid(map_copy);
}

static void	check_map_height_and_malloc(t_game *game, t_map *map)
{
	map->height = ft_lstsize(map->line_list);
	if (map->height == 0)
	{
		ft_lstclear(&map->line_list, free);
		exit_safe(game, "The map is empty", 1);
	}
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (map->grid == NULL)
	{
		ft_lstclear(&map->line_list, free);
		exit_safe(game, "Malloc (map grid)", 1);
	}
}

static void	copy_lines_to_grid(t_game *game, t_map *map)
{
	int		i;
	char	*line_copy;
	t_list	*current_node;	

	i = 0;
	current_node = map->line_list;
	while (current_node != NULL)
	{
		line_copy = ft_strdup((char *)current_node->content);
		if (!line_copy)
		{
			while (i > 0)
			{
				i--;
				free(map->grid[i]);
			}
			free(map->grid);
			ft_lstclear(&map->line_list, free);
			exit_safe(game, "Line copy could not created", 1);
		}
		map->grid[i] = line_copy;
		i++;
		current_node = current_node->next;
	}
	map->grid[i] = NULL;
}

void	finalize_map_grid(t_game *game, t_map *map)
{
	check_map_height_and_malloc(game, map);
	copy_lines_to_grid(game, map);
	ft_lstclear(&map->line_list, free);
}
