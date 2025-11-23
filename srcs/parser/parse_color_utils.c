/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:34:11 by azorlutu          #+#    #+#             */
/*   Updated: 2025/11/22 15:34:12 by azorlutu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_valid_color(t_game *game, char *color_token)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (color_token[i])
	{
		if (color_token[i] == ',')
			comma_count++;
		else if ((color_token[i] != '+' && color_token[i] != '-'
				&& color_token[i] != ' ') && !ft_isdigit(color_token[i]))
			exit_safe(game, "Color definition contains invalid characters", 1);
		if (color_token[i] == ' ' && (i > 0 && color_token[i + 1]))
		{
			if (ft_isdigit(color_token[i + 1])
				&& ft_isdigit(color_token[i - 1]))
				exit_safe(game, "Spaces are not "
					"allowed around commas in color definition", 1);
		}
		i++;
	}
	if (comma_count != 2)
		exit_safe(game, "Color definition must contain exactly two commas", 1);
}

void	check_color_tokens(t_game *game, int *target_color, char **tokens)
{
	tokens[1] = merge_color_tokens(game, tokens);
	if (!tokens[1])
		exit_safe(game, "Malloc error during color token merge", 1);
	check_valid_color(game, tokens[1]);
	if (tokens[1] == NULL || tokens[2] != NULL)
		exit_safe(game, "Wrong color definition. (Ex: 'F R,G,B')", 1);
	if (*target_color != -1)
		exit_safe(game, "Color duplicate detected", 1);
}

char	**split_and_check_rgb(t_game *game, char *rgb_token)
{
	int	i;

	i = 0;
	game->parser_state.rgb_colors = ft_split(rgb_token, ',');
	while (game->parser_state.rgb_colors[i]
		&& is_digit_string(game->parser_state.rgb_colors[i]))
		i++;
	if (i != 3)
		exit_safe(game, "RGB colors should be three", 1);
	return (game->parser_state.rgb_colors);
}

void	check_rgb_range(t_game *game, int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_safe(game, "Color range must be between 0-255", 1);
}
