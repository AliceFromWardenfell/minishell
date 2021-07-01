/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airon <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:33:24 by airon             #+#    #+#             */
/*   Updated: 2020/11/11 18:33:26 by airon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in_trim_set(char c, char const *set)
{
	while (*set != '\0')
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	max_str;
	size_t	min_str;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	min_str = 0;
	while (ft_in_trim_set(s1[min_str], set) && s1[min_str])
		min_str++;
	max_str = ft_strlen(s1);
	while (max_str && ft_in_trim_set(s1[max_str - 1], set))
		max_str--;
	if (max_str <= min_str)
		return (ft_strdup(""));
	res = ft_substr(s1, min_str, max_str - min_str);
	return (res);
}
