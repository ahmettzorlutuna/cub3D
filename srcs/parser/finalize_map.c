/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 21:10:36 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/23 21:10:36 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void validate_map_content(t_game *game)
{
	int		x;
	int		y;
	int		player_x;
	int		player_y;
	int		player_count;
	char	current_char;

	x = -1;
	y = -1;
	player_count = 0;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x] != '\0')
		{
			current_char = game->map.grid[y][x];
			if(!ft_strchr("01NWSE", current_char))
				print_error_and_exit("Invalid char found in the map");
			if(!ft_strchr("NWSE",current_char))
			{
				player_count++;
				player_x = x;
				player_y = y;
			}
			x++;
		}
		y++;
	}
	if(player_count != 1)
		print_error_and_exit("There should be 1 player on the map.");
	game->player.pos.x = (double)player_x + 0.5;
	game->player.pos.y = (double)player_y + 0.5;
}

void finalize_map_grid(t_map *map)
{
    int		i;
    t_list	*current_node;
	char	*line_copy;

    map->height = ft_lstsize(map->line_list);
    if(map->height == 0)
    {
        ft_lstclear(&map->line_list, free);
        print_error_and_exit("The map is empty");
    }
    map->grid = malloc(sizeof(char *) * (map->height + 1));
    if(map->grid == NULL)
    {
        ft_lstclear(&map->line_list, free);
        print_error_and_exit("Malloc (map grid)");
    }
	i = 0;
	current_node = map->line_list;
	while (current_node != NULL)
	{
		line_copy = ft_strdup((char *)current_node->content);
		if(!line_copy)
		{
			while (i > 0)
			{
				i--;
				free(map->grid[i]);
			}
			free(map->grid);
			ft_lstclear(&map->line_list, free);
			print_error_and_exit("Line copy could not created");
		}
		map->grid[i] = line_copy;
		i++;
		current_node = current_node->next;
	}
	map->grid[i] = NULL;
	ft_lstclear(&map->line_list, free);
}