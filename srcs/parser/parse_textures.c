/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:36:02 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/19 22:36:03 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parse_texture(t_game *game, char **target_path, char **tokens)
{
	int		texture_path_len;
	int		fd;

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
	check_hidden_file(game, tokens[1], "The texture file cannot be hidden");
	if (*target_path == NULL)
		exit_safe(game, "fd: malloc error", 1);
}

void	check_hidden_file(t_game *game, char *path, char *error_msg)
{
	char	*arg;

	arg = ft_strrchr(path, '/');
	if (arg && arg[1] == '.')
	{
		if (ft_strlen(++arg) == 4)
			exit_safe(game, error_msg, 1);
		exit_safe(game, error_msg, 1);
	}
	if (!arg && path[0] == '.')
		exit_safe(game, error_msg, 1);
}
