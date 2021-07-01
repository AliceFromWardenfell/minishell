/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airon <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:24:19 by airon             #+#    #+#             */
/*   Updated: 2020/11/11 18:24:33 by airon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	unsigned long int	result;
	unsigned long int	max;
	int					sign;

	sign = 1;
	result = 0;
	max = LONG_MAX;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (sign == -1 && (max + 1 - *str + '0') < result * 10)
			return (0);
		else if (sign == 1 && (max - *str + '0') < result * 10)
			return (-1);
		result = result * 10 + *(str++) - '0';
	}
	return ((int)(result * sign));
}
