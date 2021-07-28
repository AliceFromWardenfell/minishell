#include "minishell.h"

int	pwd_b(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		printf("minishell: pwd: %s\n", strerror(errno));
		return (0);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}
