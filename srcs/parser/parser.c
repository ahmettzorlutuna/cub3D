/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 23:11:36 by azorlutu          #+#    #+#             */
/*   Updated: 2025/11/10 20:47:45 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	void	process_identifier(t_game *game, char *line,
		char **tokens)
{
	if (ft_strncmp(tokens[0], "NO", 3) == 0)
		parse_texture(game, &game->map.north_texture_path, tokens);
	else if (ft_strncmp(tokens[0], "SO", 3) == 0)
		parse_texture(game, &game->map.south_texture_path, tokens);
	else if (ft_strncmp(tokens[0], "WE", 3) == 0)
		parse_texture(game, &game->map.west_texture_path, tokens);
	else if (ft_strncmp(tokens[0], "EA", 3) == 0)
		parse_texture(game, &game->map.east_texture_path, tokens);
	else if (ft_strncmp(tokens[0], "F", 2) == 0)
		parse_color(game, &game->map.floor_color, tokens);
	else if (ft_strncmp(tokens[0], "C", 2) == 0)
		parse_color(game, &game->map.ceiling_color, tokens);
	else
	{
		game->map.is_map_started = 1;
		handle_map_line(game, line);
	}
}

static	int	skip_empty_or_null_line(t_game *game, char **trimmed_line)
{
	if (!*trimmed_line)
		return (1);
	if ((*trimmed_line)[0] == '\0')
	{
		free(*trimmed_line);
		game->parser_state.trimmed_line = NULL;
		*trimmed_line = NULL;
		return (1);
	}
	return (0);
}

static	void	process_map_line(t_game *game, char *line)
{
	char	*trimmed_line;
	char	**tokens;

	tokens = NULL;
	if (game->map.is_map_started != 1)
		trimmed_line = ft_strtrim(line, " \t\n");
	else
		trimmed_line = ft_strtrim(line, " \t");
	game->parser_state.trimmed_line = trimmed_line;
	if (skip_empty_or_null_line(game, &trimmed_line))
		return ;
	tokens = ft_split(trimmed_line, ' ');
	game->parser_state.tokens = tokens;
	process_identifier(game, line, tokens);
	if (tokens)
	{
		free_string_array(tokens);
		game->parser_state.tokens = NULL;
	}
	if (trimmed_line)
	{
		free(trimmed_line);
		game->parser_state.trimmed_line = NULL;
	}
}

void	parse_map_lines(char *file_name, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit_safe(game, "File cannot open", 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		game->parser_state.line = line;
		process_map_line(game, line);
		free(line);
		game->parser_state.line = NULL;
		line = get_next_line(fd);
	}
	close(fd);
}
