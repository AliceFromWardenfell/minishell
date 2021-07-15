#include "libft.h"
#include <limits.h>

static int	change_overflow(int a, int *overflow)
{
	*overflow = 1;
	return (a);
}

long int	ft_atol(const char *nptr, int *overflow)
{
	unsigned long int	result;
	unsigned long int	max;
	int					sign;

	sign = 1;
	result = 0;
	max = LONG_MAX;
	*overflow = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
		|| *nptr == '\v' || *nptr == '\f' || *nptr == '\r')
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{	
		if (sign == -1 && (max + 1 - *nptr + '0') < result * 10)
			return (change_overflow(0, overflow));
		else if (sign == 1 && (max - *nptr + '0') < result * 10)
			return (change_overflow(-1, overflow));
		result = result * 10 + *(nptr++) - '0';
	}
	return ((long int)(result * sign));
}
