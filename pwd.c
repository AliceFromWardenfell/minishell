#include "minishell.h"

int	pwd_b(void) 
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		printf("minishell: pwd: %s\n", strerror(errno)); //simulate error on stdout
		return (0);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}
