#include "executor.h"

int		global_error()
{
	//here will be all frees and maybe closes of unclosed fds
	
	if (g_backup.fd_out != -1)
	{
		if (dup2(g_backup.fd_out, 1) < 0)
			exit(1);
		if (close(g_backup.fd_out) < 0)
			exit(1);
	}
		
	if (g_backup.fd_in != -1)
	{
		if (dup2(g_backup.fd_in, 0) < 0)
			exit(1);
		if (close(g_backup.fd_in) < 0)
			exit(1);
	}
	
	printf("errno is %d\n", errno); // remove
	printf("%s\n", strerror(errno));
	return (1);
}