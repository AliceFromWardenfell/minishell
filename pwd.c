#include "executor.h"

int	pwd_b(void) 
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		printf("%s\n", strerror(errno)); //simulate error on stdout
		return (0);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}
