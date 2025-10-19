/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:36:02 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/19 22:36:03 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    validate_arguments(int argc, char **argv)
{
    int len;

    if (argc != 2)
	{
        ft_putstr_fd("Usage: ./cub3D <map_file.cub>\n",2);
		exit(1);
	}
    
    len = ft_strlen(argv[1]);
    if (len < 5 || ft_strncmp(&argv[1][len - 4], ".cub", 5) != 0)
	{
        ft_putstr_fd("The map file name must have the .cub extension.\n",2);
		exit(1);
	}
}