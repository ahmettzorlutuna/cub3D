/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:36:02 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/19 22:36:03 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_prefix_and_sign(const char *str, int *sign)
{
	int	i;

	i = 0;
	*sign = 2;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = -1;
		else if (str[i] == '+')
			*sign = 1;
		i++;
	}
	while (str[i] == '0')
		i++;
	return (i);
}

static int	lunatoi(t_game *game, const char *str)
{
	int	result;
	int	sign;
	int	i;
	int	step;

	result = 0;
	step = 0;
	i = get_prefix_and_sign(str, &sign);
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			exit_safe(game, "RGB value has invalid sign", 1);
		if (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + (str[i] - '0');
			step++;
		}
		i++;
	}
	if (sign != 2 && result == 0)
		exit_safe(game, "RGB value has invalid sign", 1);
	if (step > 3)
		exit_safe(game, "RGB value is too large", 1);
	return (ft_atoi(str));
}

static char	*append_and_free(t_game *game, char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	if (!new_str)
		exit_safe(game, "Malloc error during color token merge", 1);
	return (new_str);
}

char	*merge_color_tokens(t_game *game, char **tokens)
{
	char	*merged;
	int		i;

	if (!tokens[0] || !tokens[1])
		exit_safe(game, "Invalid color tokens", 1);
	merged = ft_strdup(tokens[1]);
	if (!merged)
		exit_safe(game, "Malloc error during color token merge", 1);
	free(tokens[1]);
	merged = append_and_free(game, merged, " ");
	i = 2;
	while (tokens[i])
	{
		merged = append_and_free(game, merged, tokens[i]);
		merged = append_and_free(game, merged, " ");
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	return (merged);
}

void	parse_color(t_game *game, int *target_color, char **tokens)
{
	int		r;
	int		g;
	int		b;
	int		final_color;

	check_color_tokens(game, target_color, tokens);
	game->parser_state.rgb_colors = split_and_check_rgb(game, tokens[1]);
	r = lunatoi(game, game->parser_state.rgb_colors[0]);
	g = lunatoi(game, game->parser_state.rgb_colors[1]);
	b = lunatoi(game, game->parser_state.rgb_colors[2]);
	if (game->parser_state.rgb_colors)
	{
		free_string_array(game->parser_state.rgb_colors);
		game->parser_state.rgb_colors = NULL;
	}
	check_rgb_range(game, r, g, b);
	final_color = (r << 16) | (g << 8) | b;
	*target_color = final_color;
}
