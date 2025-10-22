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

void parse_color(t_game *game, int *target_color, char **tokens)
{
    (void)game;
    char    **rgb_colors;
    int     r;
    int     g;
    int     b;
    int     final_color;

    if (tokens[1] == NULL || tokens[2] != NULL)
        print_error_and_exit("Wrong color definition. (Ex: 'F R,G,B')");
    if(*target_color != -1)
        print_error_and_exit("Color duplicate detected");
    rgb_colors = ft_split(tokens[1],',');
    if(!rgb_colors[0] || !rgb_colors[1] || !rgb_colors[2] || rgb_colors[3] != NULL)
        print_error_and_exit("RGB colors should be three");
    if(!is_digit_string(rgb_colors[0]) || !is_digit_string(rgb_colors[1]) ||  !is_digit_string(rgb_colors[2]))
    {
        free_string_array(rgb_colors);
        print_error_and_exit("RGB color type must be integer");
    }
    r = ft_atoi(rgb_colors[0]);
    g = ft_atoi(rgb_colors[1]);
    b = ft_atoi(rgb_colors[2]);
    free_string_array(rgb_colors);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        print_error_and_exit("Color range must be between 0-255");
    final_color = (r << 16) | (g << 8) | b;
    *target_color = final_color;
}

void parse_texture(char **target_path, char **tokens)
{
    int texture_path_len;
    int fd;

    if(tokens[1] == NULL || tokens[2] != NULL)
        print_error_and_exit("Your texture use is not correct (Ex. 'NO ./path')");

    if(*target_path != NULL)
        print_error_and_exit("Texture path duplicate detected");

    texture_path_len = ft_strlen(tokens[1]);
    if(texture_path_len < 5 || ft_strncmp(&tokens[1][texture_path_len - 4], ".xpm", 5) != 0)
        print_error_and_exit("Texture path must ends with .xpm");
    fd = open(tokens[1], O_RDONLY);
    if(fd < 0)
        print_error_and_exit("This file cannot read");
    else
        close(fd);
    *target_path = ft_strdup(tokens[1]);
    if(*target_path == NULL)
        print_error_and_exit("fd: malloc error");
}

void parse_mapfile(char *file_name, t_game *game)
{
    int     fd;
    char    *line;
    char    *trimmed_line;
    char    **tokens;
    char    *line_copy;
    t_list  *new_node;
    
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
            parse_texture(&game->map.north_texture_path, tokens);
        else if (ft_strncmp(tokens[0], "SO", 3) == 0)
            parse_texture(&game->map.south_texture_path, tokens);
        else if (ft_strncmp(tokens[0], "WE", 3) == 0)
            parse_texture(&game->map.west_texture_path, tokens);
        else if (ft_strncmp(tokens[0], "EA", 3) == 0)
            parse_texture(&game->map.east_texture_path, tokens);
        else if (ft_strncmp(tokens[0], "F", 2) == 0)
            parse_color(game, &game->map.floor_color, tokens);
        else if (ft_strncmp(tokens[0], "C", 2) == 0)
            parse_color(game, &game->map.ceiling_color, tokens);
        else
        {
            if (game->map.north_texture_path == NULL || \
                game->map.south_texture_path == NULL || \
                game->map.west_texture_path  == NULL || \
                game->map.east_texture_path  == NULL || \
                game->map.floor_color        == -1   || \
                game->map.ceiling_color      == -1)
            {
                free_string_array(tokens);
                free(trimmed_line);
                free(line);
                print_error_and_exit("The map started before all elements (NO, SO, WE, EA, F, C) were defined");
            }
            line_copy = create_map_line_copy(line);
            if(!line_copy)
                print_error_and_exit("The line copy could not created");
            new_node = ft_lstnew(line_copy);
            if(!new_node)
                print_error_and_exit("The node could not created");
            ft_lstadd_back(&game->map.line_list, new_node);
            free_string_array(tokens);
            tokens = NULL;
            free(trimmed_line);
            trimmed_line = NULL;
        }
        if (tokens)
            free_string_array(tokens);
        if (trimmed_line)
            free(trimmed_line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
}