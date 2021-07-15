/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airon <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:50:19 by airon             #+#    #+#             */
/*   Updated: 2020/11/16 18:50:24 by airon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_length;

	little_length = 0;
	while (little[little_length] != '\0')
		little_length++;
	if (!little_length)
		return ((char *)big);
	while (*big != '\0' && len >= little_length)
	{
		i = 0;
		while (big[i] == little[i])
		{
			if (little[i + 1] == '\0')
				return ((char *)big);
			i++;
		}
		big++;
		len--;
	}
	return (NULL);
}
