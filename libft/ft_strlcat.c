/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airon <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:32:19 by airon             #+#    #+#             */
/*   Updated: 2020/11/11 18:32:20 by airon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	destlength;
	size_t	srclength;

	srclength = 0;
	destlength = 0;
	while (src[srclength] != '\0')
		srclength++;
	while (dst[destlength] != '\0' && destlength < size)
		destlength++;
	if (destlength == size)
		return (size + srclength);
	i = 0;
	while (src[i] != '\0' && i < size - destlength - 1)
	{
		dst[destlength + i] = src[i];
		i++;
	}
	dst[destlength + i] = '\0';
	return (destlength + srclength);
}
