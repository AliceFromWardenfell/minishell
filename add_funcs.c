#include "executor.h"

void	print_2d(char **arr) //tmp func
{
	int		i;

	i = -1;
	while (arr[++i])
		printf("%d. %s\n", i, arr[i]);
}
