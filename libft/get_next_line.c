/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airon <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 20:50:58 by airon             #+#    #+#             */
/*   Updated: 2020/12/22 20:51:00 by airon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static char	*strjoin_free(char *line, char *buffer)
{
	char	*tmp;

	tmp = line;
	line = ft_strjoin(tmp, buffer);
	free(tmp);
	return (line);
}

static int	new_line_check(t_gnl_list *current, char **line)
{
	char	*tmp;

	tmp = current->buffer;
	current->buffer = ft_strchr(current->buffer, '\n');
	if (current->buffer)
	{
		*(current->buffer) = '\0';
		*line = strjoin_free(*line, tmp);
		if (!*line)
		{
			*(current->buffer) = '\n';
			current->buffer = tmp;
			return (1);
		}
		(current->buffer)++;
		return (1);
	}
	current->buffer = tmp;
	return (0);
}

static int	line_reader(t_gnl_list *current, int fd, char **line)
{
	int	n;

	if (new_line_check(current, line))
		return (1);
	*line = strjoin_free(*line, current->buffer);
	if (!(*line))
		return (1);
	n = read(fd, current->buffer_start, 32);
	while (n > 0)
	{
		current->buffer_start[n] = '\0';
		current->buffer = current->buffer_start;
		if (new_line_check(current, line))
			return (1);
		*line = strjoin_free(*line, current->buffer_start);
		if (!(*line))
			return (1);
		n = read(fd, current->buffer_start, 32);
	}
	if (check_n(n, line))
		return (1);
	return (0);
}

int	line_start_check(int fd, char **line, t_gnl_list **start)
{
	if (!line)
		return (-1);
	*line = NULL;
	if (fd < 0)
		return (-1);
	if (!(*start))
	{	
		*start = gnl_lstnew(fd);
		if (!(*start))
			return (-1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static t_gnl_list	*start;
	t_gnl_list			*current;

	if (line_start_check(fd, line, &start) == -1)
		return (-1);
	current = gnl_lstfind(fd, start);
	if (!current)
		return (-1);
	*line = (char *)malloc(1);
	if (!(*line))
		return (-1);
	*line[0] = '\0';
	if (!line_reader(current, fd, line))
	{
		gnl_lstdel(&start, fd);
		return (0);
	}
	else if (!*line)
		return (-1);
	else
		return (1);
}
