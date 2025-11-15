/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:36:02 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/19 22:36:03 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	char	*merge_color_tokens(t_game *game, char **tokens)
{
	char	*merged;
	char	*tmp;
	int		i;

	if (!tokens[0] || !tokens[1])
		exit_safe(game, "Invalid color tokens", 1);
	merged = ft_strdup(tokens[1]);
	if (!merged)
		exit_safe(game, "Malloc error during color token merge", 1);
	free(tokens[1]);
	i = 2;
	while (tokens[i])
	{
		tmp = ft_strdup(merged);
		free(merged);
		merged = ft_strjoin(tmp, tokens[i]);
		if (!merged)
			exit_safe(game, "Malloc error during color token merge", 1);
		free(tmp);
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	return (merged);
}

static void	check_color_tokens(t_game *game, int *target_color, char **tokens)
{
	tokens[1] = merge_color_tokens(game, tokens);
	if (tokens[1] == NULL || tokens[2] != NULL)
		exit_safe(game, "Wrong color definition. (Ex: 'F R,G,B')", 1);
	if (*target_color != -1)
		exit_safe(game, "Color duplicate detected", 1);
}

static char	**split_and_check_rgb(t_game *game, char *rgb_token)
{
	char	**rgb_colors;

	rgb_colors = ft_split(rgb_token, ',');
	if (!rgb_colors[0] || !rgb_colors[1]
		|| !rgb_colors[2] || rgb_colors[3] != NULL)
	{
		free_string_array(rgb_colors);
		exit_safe(game, "RGB colors should be three", 1);
	}
	if (!is_digit_string(rgb_colors[0]) || !is_digit_string(rgb_colors[1])
		|| !is_digit_string(rgb_colors[2]))
	{
		free_string_array(rgb_colors);
		exit_safe(game, "RGB color type must be integer", 1);
	}
	return (rgb_colors);
}

static void	check_rgb_range(t_game *game, int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_safe(game, "Color range must be between 0-255", 1);
}

void	parse_color(t_game *game, int *target_color, char **tokens)
{
	char	**rgb_colors;
	int		r;
	int		g;
	int		b;
	int		final_color;

	check_color_tokens(game, target_color, tokens);
	rgb_colors = split_and_check_rgb(game, tokens[1]);
	r = ft_atoi(rgb_colors[0]);
	g = ft_atoi(rgb_colors[1]);
	b = ft_atoi(rgb_colors[2]);
	free_string_array(rgb_colors);
	check_rgb_range(game, r, g, b);
	final_color = (r << 16) | (g << 8) | b;
	*target_color = final_color;
}
