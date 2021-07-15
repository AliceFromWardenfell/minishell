/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airon <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:30:21 by airon             #+#    #+#             */
/*   Updated: 2020/11/11 18:30:22 by airon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char	*temp1;
	unsigned char	*temp2;

	if (!s1 && !s2)
		return (NULL);
	temp1 = (unsigned char *)s1;
	temp2 = (unsigned char *)s2;
	if (temp1 <= temp2)
	{	
		while (n)
		{
			*(temp1++) = *(temp2++);
			n--;
		}
	}
	else
	{	
		while (n)
		{
			n--;
			*(temp1 + n) = *(temp2 + n);
		}
	}
	return (s1);
}
