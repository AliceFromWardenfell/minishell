#include "executor.h"

static int	do_fork(t_cmd *cmd, t_data *d)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		return (global_error(d));

	if (!pid)
		if (execve(cmd->argv[0], cmd->argv, NULL) < 0)
			return (global_error(d)); // if execve returns < 0, we don't need to abort ALL while. We need to continue execute the commands!
	if (wait(NULL) < 0)
		return (global_error(d));
	return (0);
}

static int	execute(t_cmd *cmd, t_data *d) //check if argv[0] even exists, then do things!
{
	int		builtin;

	builtin = is_builtin(cmd);
	if (!builtin)
		if (do_fork(cmd, d))
			return (1);
	if (builtin)
		if (do_builtin(cmd, d, builtin))
			return (1);
	return (0);
}

static int	do_pipe(t_cmd *cmd, t_data *d)
{
	t_cmd	*next_cmd;
	int		pipe_fd[2];

	next_cmd = cmd->next;
	if (next_cmd && next_cmd->argv[0]) // if true, pipe exists
	{
		if (pipe(pipe_fd) < 0)
			return (global_error(d));
		next_cmd->fd_in = pipe_fd[0];
		cmd->fd_out = pipe_fd[1];
	}
	return (0);
}

static int	core_loop(t_cmd *cmd, t_data *d)
{	
	while (cmd)
	{
		if (dup2(cmd->fd_in, 0) < 0) // init has to be on 0
			return (global_error(d));
		if (cmd->fd_in)
			if (close(cmd->fd_in) < 0)
				return (global_error(d));

		if (do_pipe(cmd, d))
			return (1);

		if (dup2(cmd->fd_out, 1) < 0) // init has to be on 1
			return (global_error(d));
		if (cmd->fd_out != 1)
			if (close(cmd->fd_out) < 0)
				return (global_error(d));

		if (execute(cmd, d))
			return (1);

		cmd = cmd->next;
	}
	return (0);
}

int	executor(t_cmd *cmd, const char **envp)
{
	t_data	d;
	errno = 0; // has to be in the begining of the first-big-super while, which waits for cmds

	if (dup_envp(&d, envp))		// if (dup_envp(envp))
		return (1);							// 	return (1); //wait for handle $(VAL)
	
	print_2d((char **)envp);
	printf("*************************\n");
	print_2d(d.env);

	d.backup.fd_out = dup(1); // has to be initialize to -1
	if (d.backup.fd_out < 0)
		return (global_error(&d));

	d.backup.fd_in = dup(0); // has to be initialize to -1
	if (d.backup.fd_in < 0)
		return (global_error(&d));

	if (core_loop(cmd, &d))
		return (1);

	if (dup2(d.backup.fd_out, 1) < 0)
		return (global_error(&d));
	if (close(d.backup.fd_out) < 0)
		return (global_error(&d));
	if (dup2(d.backup.fd_in, 0) < 0)
		return (global_error(&d));
	if (close(d.backup.fd_in) < 0)
		return (global_error(&d));

	printf("*FINISHED*\n");
	return (0);
}
