/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 23:21:53 by azorlutu          #+#    #+#             */
/*   Updated: 2025/11/10 21:21:18 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_string_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static	void	free_parser_state(t_game *game)
{
	if (game == NULL)
		return ;
	if (game->parser_state.rgb_colors)
	{
		free_string_array(game->parser_state.rgb_colors);
		game->parser_state.rgb_colors = NULL;
	}
	if (game->parser_state.tokens)
	{
		free_string_array(game->parser_state.tokens);
		game->parser_state.tokens = NULL;
	}
	if (game->parser_state.trimmed_line)
	{
		free(game->parser_state.trimmed_line);
		game->parser_state.trimmed_line = NULL;
	}
	if (game->parser_state.line)
	{
		free(game->parser_state.line);
		game->parser_state.line = NULL;
	}
}

static void	exit_with_message(char *str, int exit_no)
{
	if (exit_no == 0)
		exit(0);
	print_error_and_exit(str);
}

void	exit_safe(t_game *game, char *str, int exit_no)
{
	free_gnl_buffer();
	if (game != NULL)
	{
		free_parser_state(game);
		free_textures_and_images_and_grid(game);
		free_map_paths(game);
		free_mlx_and_window(game);
	}
	exit_with_message(str, exit_no);
}

void	print_error_and_exit(char *message)
{
	if (message != NULL && *message != '\0')
		ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
