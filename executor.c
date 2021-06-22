#include "executor.h"

int		main(void)
{
	t_cmd	cmd1;
	t_cmd	cmd2;
	t_cmd	cmd3;

	cmd3.next = NULL;
	cmd2.next = &cmd3;
	cmd1.next = &cmd2;

	cmd1.argv = (char **)malloc(4 * sizeof(char*));
	cmd1.argv[0] = "summ";
	cmd1.argv[1] = "24";
	cmd1.argv[2] = "13";
	cmd1.argv[3] = NULL;
	cmd1.fd_out	= 0;
	
	cmd2.argv = (char **)malloc(4 * sizeof(char*));
	cmd2.argv[0] = "mult";
	cmd2.argv[1] = "7";
	cmd2.argv[2] = "8";
	cmd2.argv[3] = NULL;
	cmd2.fd_out = open("output", O_WRONLY | O_CREAT, 0644);

	cmd3.argv = (char **)malloc(4 * sizeof(char*));
	cmd3.argv[0] = "subtr";
	cmd3.argv[1] = "10";
	cmd3.argv[2] = "2";
	cmd3.argv[3] = NULL;
	cmd3.fd_out	= 0;
	
	/*****my part*****/

	int		pid;
	t_cmd	*tmp;
	int		tmp_fd_out;

	tmp = &cmd1;
	tmp_fd_out = dup(1);
	while (tmp)
	{
		if (tmp->fd_out)
			dup2(tmp->fd_out, 1);
		pid = fork();
		if (!pid)
			if (execve(tmp->argv[0], tmp->argv, NULL) < 0)
			{
				printf("ERROR: execve\n");
				return(-1);
			}
		wait(NULL);
		dup2(tmp_fd_out, 1);
		tmp = tmp->next;
	}
	printf("*SUCCESS*\n");
	return (0);
}