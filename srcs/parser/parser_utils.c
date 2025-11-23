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

void	print_map_copy(char **map_copy, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{
		printf("%s\n", map_copy[y]);
		y++;
	}
}

void	free_grid(char **grid)
{
	int	y;

	y = 0;
	if (!grid)
		return ;
	while (grid[y])
	{
		free(grid[y]);
		y++;
	}
	free(grid);
}

char	*create_map_line_copy(char *line)
{
	size_t	len;
	size_t	copy_len;

	if (line == NULL)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		copy_len = len - 1;
	else
		copy_len = len;
	return (ft_substr(line, 0, copy_len));
}

void	validate_arguments(t_game *game, int argc, char **argv)
{
	int		len;
	char	*arg;

	len = ft_strlen(argv[1]);
	arg = ft_strrchr(argv[1], '/');
	if (argc != 2)
		exit_safe(game, "Usage: ./cub3D <map_file.cub>\n", 1);
	if (arg[1] == '.')
	{
		if (ft_strlen(++arg) == 4)
			exit_safe(game, "The map file need name.\n", 1);
		exit_safe(game, "File cannot be secret.\n", 1);
	}
	if (len < 5 || ft_strncmp(&argv[1][len - 4], ".cub", 5) != 0)
		exit_safe(game,
			"The map file name must have the .cub extension.\n", 1);
}

int	is_digit_string(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[0] == '\0')
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}
