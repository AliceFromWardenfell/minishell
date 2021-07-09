#include "executor.h"

int	env_b(t_data *d)
{
	int		i;

	i = -1;
	while (d->env[++i])
		printf("%s\n", d->env[i]);
	return (0);
}
