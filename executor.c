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
	cmd1.argv[0] = "subtr";
	cmd1.argv[1] = NULL;
	cmd1.fd_out	= 1;
	cmd1.fd_in	= open("input", O_RDONLY, 0644);
	
	cmd2.argv = (char **)malloc(4 * sizeof(char*));
	cmd2.argv[0] = "pow2";
	cmd2.argv[1] = NULL;
	cmd2.fd_out = 1;
	cmd2.fd_in = 0;

	cmd3.argv = (char **)malloc(4 * sizeof(char*));
	cmd3.argv[0] = "plus5";
	cmd3.argv[1] = NULL;
	cmd3.fd_out	= open("output", O_WRONLY | O_CREAT, 0644);
	cmd3.fd_in	= 0;

	
	/*****my part*****/

	int		pid;
	t_cmd	*tmp;
	t_cmd	*tmp_next;
	int		old_fd_out;
	int		old_fd_in;
	int		pipe_fd[2];

	tmp = &cmd1;
	old_fd_out = dup(1); // save old
	old_fd_in = dup(0);
	while (tmp)
	{
		dup2(tmp->fd_in, 0); // init has to be on 0
		if (tmp->fd_in)
			close(tmp->fd_in);
		tmp_next = tmp->next;
		if (tmp_next && tmp_next->argv[0]) // if true, pipe exists
		{
			pipe(pipe_fd);
			tmp_next->fd_in = pipe_fd[0];
			tmp->fd_out = pipe_fd[1];
		}
		dup2(tmp->fd_out, 1); // init has to be on 1
		if (tmp->fd_out != 1)
			close(tmp->fd_out);
		pid = fork();
		if (!pid)
			if (execve(tmp->argv[0], tmp->argv, NULL) < 0)
			{
				printf("ERROR: execve\n");
				return(-1);
			}
		wait(NULL);
		tmp = tmp->next;
	}
	dup2(old_fd_out, 1);
	close(old_fd_out);
	dup2(old_fd_in, 0);
	close(old_fd_in);
	printf("*SUCCESS*\n");
	return (0);
}