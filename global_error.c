#include "executor.h"

int		global_error(t_data *d)
{
	//here will be all frees and maybe closes of unclosed fds
	
	if (d->backup->fd_out != -1)
	{
		if (dup2(d->backup->fd_out, 1) < 0)
			exit(1);
		if (close(d->backup->fd_out) < 0)
			exit(1);
	}
		
	if (d->backup->fd_in != -1)
	{
		if (dup2(d->backup->fd_in, 0) < 0)
			exit(1);
		if (close(d->backup->fd_in) < 0)
			exit(1);
	}
	
	printf("errno is %d\n", errno); // remove
	printf("%s\n", strerror(errno));
	return (1);
}