/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:26:51 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/25 19:26:52 by azorlutu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    flood_fill(char **map_copy, int height, int x, int y)
{
    if(y < 0 || y >= height || map_copy[y] == NULL)
    {
        free_grid(map_copy);
        print_error_and_exit("Map open vertically");
    }
    if(x < 0 || x >= (int)ft_strlen(map_copy[y]))
    {
        free_grid(map_copy);
        print_error_and_exit("Map open horizontally");
    }
    if (map_copy[y][x] == '1' || map_copy[y][x] == 'F')
        return ;
    if (map_copy[y][x] == ' ')
    {
        free_grid(map_copy);
        print_error_and_exit("There should be no gaps in the map!");
    }
    if (ft_strchr("0NSEW", map_copy[y][x]))
        map_copy[y][x] = 'F';
    flood_fill(map_copy, height, x, y + 1);
	flood_fill(map_copy, height, x, y - 1);
	flood_fill(map_copy, height, x + 1, y);
	flood_fill(map_copy, height, x - 1, y);
}