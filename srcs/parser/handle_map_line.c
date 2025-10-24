/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:48:52 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/23 20:48:53 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int all_elements_defined(t_game *game)
{
    if (game->map.north_texture_path == NULL || \
        game->map.south_texture_path == NULL || \
        game->map.west_texture_path  == NULL || \
        game->map.east_texture_path  == NULL || \
        game->map.floor_color        == -1   || \
        game->map.ceiling_color      == -1)
        return (0);
    return (1);
}

static void handle_parse_error(char *message, char **tokens, char *trimmed_line, char *line)
{
    free_string_array(tokens);
    free(trimmed_line);
    free(line);
    print_error_and_exit(message);
}

void handle_map_line(t_game *game, char *line, char **tokens, char *trimmed_line)
{
    char    *line_copy;
    t_list  *new_node;

    if (!all_elements_defined(game))
        handle_parse_error("The map started before all elements were defined.",tokens, trimmed_line, line);
    line_copy = create_map_line_copy(line);
    if (!line_copy)
        handle_parse_error("Map line could not copy (malloc).",tokens, trimmed_line, line);
    new_node = ft_lstnew(line_copy);
    if (!new_node)
        handle_parse_error("List node could not created (malloc).",tokens, trimmed_line, line);
    ft_lstadd_back(&game->map.line_list, new_node);
}