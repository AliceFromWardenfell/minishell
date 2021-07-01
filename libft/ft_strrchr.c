/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airon <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:33:15 by airon             #+#    #+#             */
/*   Updated: 2020/11/11 18:33:17 by airon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;

	temp = (char *)s;
	while (*temp != '\0')
		temp++;
	while (temp != s)
	{
		if (*temp == (char)c)
			return (temp);
		temp--;
	}
	if (*temp == (char)c)
		return (temp);
	else
		return (NULL);
}
