#include "executor.h"

int		main(void)
{
	char	*str;

	str = malloc(4);
	ft_bzero(str, 4);
	str[4] = '\0';
	printf("Hello, world!\n");
	printf("%s\n", str);
	return (0);	
}