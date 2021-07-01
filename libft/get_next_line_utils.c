/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airon <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 20:51:21 by airon             #+#    #+#             */
/*   Updated: 2020/12/22 20:51:23 by airon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_gnl_list	*gnl_lstnew(int fd)
{
	t_gnl_list	*res;

	res = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	if (!res)
		return (NULL);
	res->fd = fd;
	res->buffer_start = (char *)malloc(33);
	if (!res->buffer_start)
	{
		free(res);
		return (NULL);
	}
	res->buffer_start[0] = '\0';
	res->buffer = res->buffer_start;
	res->next = NULL;
	return (res);
}

t_gnl_list	*gnl_lstfind(int fd, t_gnl_list *start)
{
	while (start->fd != fd && start->next)
		start = start->next;
	if (start->fd == fd)
		return (start);
	else
	{
		start->next = gnl_lstnew(fd);
		return (start->next);
	}
}

void	gnl_lstdel(t_gnl_list **start, int fd)
{
	t_gnl_list	*tmp1;
	t_gnl_list	*tmp2;

	tmp1 = *start;
	tmp2 = NULL;
	while (tmp1->fd != fd)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->next;
	}
	if (!tmp2)
	{
		*start = tmp1->next;
		free(tmp1->buffer_start);
		free(tmp1);
	}
	else
	{
		tmp2->next = tmp1->next;
		free(tmp1->buffer_start);
		free(tmp1);
	}
}

int	check_n(int n, char **line)
{
	if (n < 0)
	{
		free(*line);
		*line = NULL;
		return (1);
	}
	return (0);
}
