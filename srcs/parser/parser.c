/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 23:11:36 by azorlutu          #+#    #+#             */
/*   Updated: 2025/11/10 20:47:45 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	parse_texture(t_game *game, char **target_path, char **tokens)
{
	int	texture_path_len;
	int	fd;

	if (tokens[1] == NULL || tokens[2] != NULL)
		exit_safe(game, "Your texture use is not correct "
			"(Ex. 'NO ./path')", 1);
	if (*target_path != NULL)
		exit_safe(game, "Texture path duplicate detected", 1);
	texture_path_len = ft_strlen(tokens[1]);
	if (texture_path_len < 5
		|| ft_strncmp(&tokens[1][texture_path_len - 4], ".xpm", 5) != 0)
		exit_safe(game, "Texture path must ends with .xpm", 1);
	fd = open(tokens[1], O_RDONLY);
	if (fd < 0)
		exit_safe(game, "This file cannot read", 1);
	else
		close(fd);
	*target_path = ft_strdup(tokens[1]);
	if (*target_path == NULL)
		exit_safe(game, "fd: malloc error", 1);
}

static	void	process_identifier(t_game *game, char *line,
		char **tokens, char *trimmed_line)
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
		handle_map_line(game, line, tokens, trimmed_line);
	}
}

static	int	skip_empty_or_null_line(char **trimmed_line)
{
	if (!*trimmed_line)
		return (1);
	if ((*trimmed_line)[0] == '\0')
	{
		free(*trimmed_line);
		*trimmed_line = NULL;
		return (1);
	}
	return (0);
}

static	void	process_map_line(t_game *game, char *line)
{
	char	*trimmed_line;
	char	**tokens;

	if (game->map.is_map_started != 1)
		trimmed_line = ft_strtrim(line, " \t\n");
	else
		trimmed_line = ft_strtrim(line, " \t");
	if (skip_empty_or_null_line(&trimmed_line))
		return ;
	tokens = ft_split(trimmed_line, ' ');
	process_identifier(game, line, tokens, trimmed_line);
	if (tokens)
		free_string_array(tokens);
	if (trimmed_line)
		free(trimmed_line);
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
		process_map_line(game, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
