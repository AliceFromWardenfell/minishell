/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airon <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:26:45 by airon             #+#    #+#             */
/*   Updated: 2020/11/11 18:26:47 by airon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_array_count(int n)
{
	unsigned int	i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
		i = 1;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static void	ft_reverse(char *str)
{
	char			temp;
	int				i;
	int				j;

	i = 0;
	if (str[i] == '-')
		i++;
	j = ft_strlen(str);
	j--;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

static void	ft_array_filler(char *str, int n)
{
	unsigned int	num;
	unsigned int	i;

	i = 0;
	if (n < 0)
	{
		num = -n;
		str[i++] = '-';
	}
	else
		num = n;
	if (!num)
		str[i++] = '0';
	while (num > 0)
	{
		str[i++] = num % 10 + '0';
		num /= 10;
	}
	str[i] = '\0';
	ft_reverse(str);
}

char	*ft_itoa(int n)
{
	char			*res;

	res = (char *)malloc(sizeof(char) * (ft_array_count(n) + 1));
	if (!res)
		return (NULL);
	ft_array_filler(res, n);
	return (res);
}
