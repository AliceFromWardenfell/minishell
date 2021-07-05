#include "executor.h"

int	pwd_b(t_data *d) 
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		printf("%s\n", strerror(errno)); //simulate error on stdout
		return (0);
	}
	printf("%s\n", buf);
	d->env = NULL; // add changing of ENV-value PWD
	free(buf);
	return (0);
}