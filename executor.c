#include "executor.h"

int		do_fork(t_cmd *cmd)
{
	int		pid;

	pid = fork();
	if (!pid)
		if (execve(cmd->argv[0], cmd->argv, NULL) < 0)
		{
			printf("ERROR: execve\n");
			return(-1);
		}
	wait(NULL);
	return (0);
}

int		do_pipe(t_cmd *cmd)
{
	t_cmd	*next_cmd;
	int		pipe_fd[2];

	next_cmd = cmd->next;
	if (next_cmd && next_cmd->argv[0]) // if true, pipe exists
	{
		pipe(pipe_fd);
		next_cmd->fd_in = pipe_fd[0];
		cmd->fd_out = pipe_fd[1];
	}
	return (0);
}

int		core_loop(t_cmd *cmd)
{
	while (cmd)
	{
		dup2(cmd->fd_in, 0); // init has to be on 0
		if (cmd->fd_in)
			close(cmd->fd_in);
		
		do_pipe(cmd);
		
		dup2(cmd->fd_out, 1); // init has to be on 1
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		
		do_fork(cmd);
		
		cmd = cmd->next;
	}
	return (0);
}

int		executor(t_cmd *cmd)
{
	int		backup_fd_out;
	int		backup_fd_in;


	backup_fd_out = dup(1); // save old
	backup_fd_in = dup(0);
	
	core_loop(cmd);
	
	dup2(backup_fd_out, 1);
	close(backup_fd_out);
	dup2(backup_fd_in, 0);
	close(backup_fd_in);
	
	printf("*SUCCESS*\n");
	return (0);
}
