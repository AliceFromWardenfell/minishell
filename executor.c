#include "executor.h"

int		do_fork(t_cmd *cmd)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		return (global_error());
	
	if (!pid)
	{
		if (execve(cmd->argv[0], cmd->argv, NULL) < 0)
			return (global_error());
	}
	if (wait(NULL) < 0)
		return (global_error());
	return (0);
}

int		do_pipe(t_cmd *cmd)
{
	t_cmd	*next_cmd;
	int		pipe_fd[2];

	next_cmd = cmd->next;
	if (next_cmd && next_cmd->argv[0]) // if true, pipe exists
	{
		if (pipe(pipe_fd) < 0)
			return (global_error());
		next_cmd->fd_in = pipe_fd[0];
		cmd->fd_out = pipe_fd[1];
	}
	return (0);
}

int		core_loop(t_cmd *cmd)
{
	while (cmd)
	{
		if (dup2(cmd->fd_in, 0) < 0) // init has to be on 0
			return (global_error());
		if (cmd->fd_in)
			if (close(cmd->fd_in) < 0)
				return (global_error());
		
		if (do_pipe(cmd))
			return (1);
		
		if (dup2(cmd->fd_out, 1) < 0) // init has to be on 1
			return (global_error());
		if (cmd->fd_out != 1)
			if (close(cmd->fd_out) < 0)
				return (global_error());
		
		if (do_fork(cmd))
			return (1);
		
		cmd = cmd->next;
	}
	return (0);
}

int		executor(t_cmd *cmd)
{

	errno = 0; // has to be in the begining of the first-big-super while, which waits for cmds
	
	g_backup.fd_out = dup(1); // has to be initialize to -1
	if (g_backup.fd_out < 0)
		return (global_error());
	
	g_backup.fd_in = dup(0); // has to be initialize to -1
	if (g_backup.fd_in < 0)
		return (global_error());
	
	if (core_loop(cmd))
		return (1);
	
	if (dup2(g_backup.fd_out, 1) < 0)
		return (global_error());
	if (close(g_backup.fd_out) < 0)
		return (global_error());
	if (dup2(g_backup.fd_in, 0) < 0)
		return (global_error());
	if (close(g_backup.fd_in) < 0)
		return (global_error());
	
	printf("*FINISHED*\n");
	return (0);
}
