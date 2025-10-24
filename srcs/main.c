/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:30:15 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/19 21:30:16 by azorlutu         ###   ########.tr       */
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
	return (0);
}