/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 23:57:49 by azorlutu          #+#    #+#             */
/*   Updated: 2024/11/28 23:57:49 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

static char	**get_remaining_storage(void)
{
	static char	*remaining;

	return (&remaining);
}

static char	*extract_line(char **remaining)
{
	char	*newline;
	char	*line;
	char	*temp;
	size_t	line_length;

	newline = ft_strchr(*remaining, '\n');
	if (!newline)
	{
		line = *remaining;
		*remaining = NULL;
		return (line);
	}
	line_length = newline - *remaining + 1;
	line = malloc(line_length + 1);
	if (!line)
		return (NULL);
	line[line_length] = '\0';
	while (line_length--)
		line[line_length] = (*remaining)[line_length];
	temp = ft_strdup(newline + 1);
	free(*remaining);
	*remaining = temp;
	return (line);
}

static int	remaining_data(int fd, char **remaining)
{
	char	*buffer;
	char	*tmp;
	ssize_t	bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!*remaining)
			*remaining = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(*remaining, buffer);
			free(*remaining);
			*remaining = tmp;
		}
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (bytes_read);
}

void	free_gnl_buffer(void)
{
	char	**remaining;

	remaining = get_remaining_storage();
	if (*remaining)
	{
		free(*remaining);
		*remaining = NULL;
	}
}

char	*get_next_line(int fd)
{
	char	*line;
	char	**remaining;

	remaining = get_remaining_storage();
	if (fd < 0 || BUFFER_SIZE == 0)
	{
		free_gnl_buffer();
		return (NULL);
	}
	if (remaining_data(fd, remaining) == -1)
	{
		free_gnl_buffer();
		return (NULL);
	}
	if (!*remaining || !**remaining)
	{
		free_gnl_buffer();
		return (NULL);
	}
	line = extract_line(remaining);
	return (line);
}
