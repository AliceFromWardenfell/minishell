#include "executor.h"

void	clean(t_data *d)
{
	int		i;

	i = -1;
	while (++i < d->amount_of_alloc_lines + 1)
		free(d->env[i]);
	if (d->env) //has to be init on NULL
		free(d->env);
}

int		global_error(t_data *d)
{
	clean(d);

	if (d->backup.fd_out != -1)
	{
		if (dup2(d->backup.fd_out, 1) < 0)
			exit(1);
		if (close(d->backup.fd_out) < 0)
			exit(1);
	}
		
	if (d->backup.fd_in != -1)
	{
		if (dup2(d->backup.fd_in, 0) < 0)
			exit(1);
		if (close(d->backup.fd_in) < 0)
			exit(1);
	}
	
	printf("errno is %d\n", errno); // remove
	printf("%s\n", strerror(errno));
	return (1);
}