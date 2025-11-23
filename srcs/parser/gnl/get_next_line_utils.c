/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 23:59:28 by azorlutu          #+#    #+#             */
/*   Updated: 2024/11/28 23:59:29 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*new_str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		new_str[i++] = *s1++;
	while (s2 && *s2)
		new_str[i++] = *s2++;
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*source;
	size_t				i;

	source = (unsigned char *)src;
	dest = (unsigned char *)dst;
	i = 0;
	if (dest == NULL && source == NULL)
	{
		return (0);
	}
	while (n > 0)
	{
		dest[i] = source[i];
		i++;
		n--;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		s1_len;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	ptr = malloc(s1_len + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, s1_len + 1);
	return (ptr);
}
