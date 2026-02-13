/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:26:25 by kjongeri          #+#    #+#             */
/*   Updated: 2025/02/20 13:45:15 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_from_file(char *stash, int fd);
static char	*extract_line(char *stash);
static char	*extract_remainder(char *stash);
static char	*read_loop(int fd, char *buffer, char *stash);

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_from_file(stash, fd);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = extract_remainder(stash);
	return (line);
}

static char	*extract_line(char *stash)
{
	char	*line;
	char	*newline;
	ssize_t	line_length;

	if (!stash)
		return (NULL);
	newline = ft_strchr(stash, '\n');
	if (!newline)
	{
		line = ft_strdup(stash);
		if (!line)
			return (NULL);
		return (line);
	}
	line_length = newline - stash + 1;
	line = ft_calloc(line_length + 1, sizeof(char));
	if (!line)
		return (NULL);
	ft_strncpy(line, stash, line_length);
	return (line);
}

static char	*extract_remainder(char *stash)
{
	char	*remainder;
	char	*newline;

	if (!stash)
		return (NULL);
	newline = ft_strchr(stash, '\n');
	if (!newline)
	{
		free(stash);
		return (NULL);
	}
	newline++;
	if (*newline == '\0')
	{
		free(stash);
		return (NULL);
	}
	remainder = ft_strdup(newline);
	if (!remainder)
	{
		free(stash);
		return (NULL);
	}
	free(stash);
	return (remainder);
}

static char	*read_from_file(char *stash, int fd)
{
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
	{
		free(stash);
		return (NULL);
	}
	stash = read_loop(fd, buffer, stash);
	free(buffer);
	return (stash);
}

static char	*read_loop(int fd, char *buffer, char *stash)
{
	char	*new_stash;
	ssize_t	bytes_read;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (!stash || bytes_read < 0)
				return (free(stash), NULL);
			break ;
		}
		buffer[bytes_read] = '\0';
		if (!stash)
			new_stash = ft_strdup(buffer);
		else
			new_stash = ft_strjoin(stash, buffer);
		free(stash);
		if (!new_stash)
			return (NULL);
		stash = new_stash;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}
