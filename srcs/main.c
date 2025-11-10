/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:30:15 by azorlutu          #+#    #+#             */
/*   Updated: 2025/11/10 20:45:22 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
	t_game game;

	validate_arguments(argc, argv);
	init_game(&game);
	parse_map_lines(argv[1], &game);
	finalize_map_grid(&game.map);
	validate_map_content(&game);
	setup_player_vectors(&game);
	create_window(&game);
	cleanup(&game);
	return (0);
}