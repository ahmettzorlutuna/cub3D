/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:48:52 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/23 20:48:53 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	int	all_elements_defined(t_game *game)
{
	if (game->map.north_texture_path == NULL
		|| game->map.south_texture_path == NULL
		|| game->map.west_texture_path == NULL
		|| game->map.east_texture_path == NULL
		|| game->map.floor_color == -1
		|| game->map.ceiling_color == -1)
		return (0);
	return (1);
}

void	handle_map_line(t_game *game, char *line)
{
	char	*line_copy;
	t_list	*new_node;

	if (!all_elements_defined(game))
		exit_safe(game,
			"Map data found before all elements were defined", 1);
	line_copy = create_map_line_copy(line);
	if (!line_copy)
		exit_safe(game, "Map line could not copy (malloc).", 1);
	new_node = ft_lstnew(line_copy);
	if (!new_node)
		exit_safe(game, "List node could not created (malloc).", 1);
	ft_lstadd_back(&game->map.line_list, new_node);
}
