/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 23:11:36 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/21 23:11:37 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void *parse_texture(t_game *game, char **target_path, char **tokens)
{
    (void)game;
    int texture_path_len;

    if(tokens[1] == NULL || tokens[2] != NULL)
        print_error_and_exit("Your texture use is not correct (Ex. 'NO ./path')");
    if(*target_path != NULL)
        print_error_and_exit("Texture path duplicate detected");
    texture_path_len = ft_strlen(tokens[1]);
    if(texture_path_len < 5 || ft_strncmp(&tokens[1][texture_path_len - 4], ".xpm", 5) != 0)
        print_error_and_exit("Texture path must ends with .xpm");
    return (0);
}

void parse_mapfile(char *file_name, t_game *game)
{
    int     fd;
    char    *line;
    char    *trimmed_line;
    char    **tokens;
    
    fd = open(file_name, O_RDONLY);
    if(fd < 0)
        print_error_and_exit("File cannot open");
    line = get_next_line(fd);
    while (line != NULL)
    {
        trimmed_line = ft_strtrim(line, " \t\n");
        free(trimmed_line);
        if(trimmed_line[0] == '\0')
        {
            free(trimmed_line);
            line = get_next_line(fd);
            continue;
        }
        tokens = ft_split(trimmed_line, ' ');
        if(!tokens)
            print_error_and_exit("ft_split could not allocate memory");
        free(trimmed_line);
        if (ft_strncmp(tokens[0], "NO", 3) == 0)
        {
            parse_texture(game, &game->map.north_texture_path, tokens);
        }
        else if (ft_strncmp(tokens[0], "SO", 3) == 0)
        {
            parse_texture(game, &game->map.south_texture_path, tokens);
        }
        else if (ft_strncmp(tokens[0], "WE", 3) == 0)
        {
            parse_texture(game, &game->map.west_texture_path, tokens);
        }
        else if (ft_strncmp(tokens[0], "EA", 3) == 0)
        {
            parse_texture(game, &game->map.east_texture_path, tokens);
        }
        else if (ft_strncmp(tokens[0], "F", 2) == 0)
        {
            // parse_color(game, &game->map.floor_color, tokens);
        }
        else if (ft_strncmp(tokens[0], "C", 2) == 0)
        {
            // parse_color(game, &game->map.ceiling_color, tokens);
        }
        else
        {
            //Map grid parser.
        }
    }
}