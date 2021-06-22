#include "executor.h"

int		main(int argc, char **argv)
{
	if (argc == 3)
	{
		printf("%d - %d = %d\n", ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[1]) - ft_atoi(argv[2]));
	}
	return (0);
}