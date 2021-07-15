/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airon <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 22:36:49 by airon             #+#    #+#             */
/*   Updated: 2021/01/19 22:36:57 by airon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	int_to_char(int n)
{
	char	res[22];

	res[0] = '0';
	res[1] = '1';
	res[2] = '2';
	res[3] = '3';
	res[4] = '4';
	res[5] = '5';
	res[6] = '6';
	res[7] = '7';
	res[8] = '8';
	res[9] = '9';
	res[10] = 'a';
	res[11] = 'b';
	res[12] = 'c';
	res[13] = 'd';
	res[14] = 'e';
	res[15] = 'f';
	res[16] = 'g';
	res[17] = 'h';
	res[18] = 'i';
	res[19] = 'j';
	res[20] = 'k';
	res[21] = 'l';
	return (res[n]);
}

void	ft_putnbr_base(long long int n, int base)
{
	unsigned long long int	num;

	if (n < 0)
		num = -n;
	else
		num = n;
	if (num / base > 0)
		ft_putnbr_base(num / base, base);
	ft_putchar(int_to_char(num % base));
}
