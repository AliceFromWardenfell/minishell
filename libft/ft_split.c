/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:31:25 by airon             #+#    #+#             */
/*   Updated: 2021/07/21 19:38:11 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_count(char const *str, char c)
{
	size_t	res;
	int		word;

	res = 0;
	word = 0;
	while (*str != '\0')
	{
		if (word == 0 && *str != c)
		{
			word = 1;
			res++;
		}
		else if (word == 1 && *str == c)
			word = 0;
		str++;
	}
	return (res);
}

static size_t	ft_word_length(char const *str, char c)
{
	size_t	res;

	res = 0;
	while (*str != '\0' && *str != c)
	{
		res++;
		str++;
	}
	return (res);
}

static void	ft_free(char **to_free)
{
	size_t	i;

	i = 0;
	while (to_free[i])
		free(to_free[i++]);
	free(to_free);
}

static int	ft_filler(char **res, char const *s, char c)
{
	size_t	i;
	int		word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (word == 0 && s[i] != c)
		{
			word = 1;
			*res = ft_substr(s, i, ft_word_length(&s[i], c));
			if (!*res)
				return (-1);
			res++;
		}
		else if (word == 1 && s[i] == c)
			word = 0;
		i++;
	}
	*res = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (!res)
		return (NULL);
	if (ft_filler(res, s, c))
	{
		ft_free(res);
		return (NULL);
	}
	return (res);
}
