/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:35:32 by cvrone            #+#    #+#             */
/*   Updated: 2021/07/22 21:40:36 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	index;

	index = 0;
	while (((unsigned char)s1[index] == (unsigned char)s2[index])
		&& ((unsigned char)s1[index] != '\0')
		&& ((unsigned char)s2[index] != '\0'))
		index++;
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}
