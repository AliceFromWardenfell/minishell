#include "minishell.h"

static int	do_fork(t_cmd *cmd, t_data *d)
{
	char	*path_to_exec;
	int		was_allocation;

	was_allocation = 0;
	path_to_exec = ft_strrchr(cmd->argv[0], '/');
	if (!path_to_exec || cmd->argv[0][0] == '/')
		path_to_exec = cmd->argv[0];
	else
		path_to_exec++;
	
	if (!has_slash(cmd->argv[0]))
		path_to_exec = search_for_exec(d, path_to_exec, &was_allocation);

	if (!path_to_exec)
		return (global_error(d));
	


	
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (global_error(d));
	if (!cmd->pid)
	{	
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(path_to_exec, cmd->argv, d->env) < 0)
		{
			if (was_allocation)
				free(path_to_exec); // mb move to global_error
			exit(global_error(d));
		}
	}
	if (was_allocation)
		free(path_to_exec);

	return (0);
}

static int	execute(t_cmd *cmd, t_data *d) //check if argv[0] even exists, then do things!
{
	int		builtin;

	builtin = is_builtin(cmd);
	if (!builtin)
		if (do_fork(cmd, d))
			return (1);
	if (builtin && !d->pipe_exists)
		do_builtin(cmd, d, builtin);
	if (builtin && d->pipe_exists)
	{
		cmd->pid = fork();
		if (cmd->pid < 0)
			return (global_error(d));
		if (!cmd->pid)
		{
			do_builtin(cmd, d, builtin); // add exit
			exit(d->status_code); // not sure about code
		}	
	}
	return (0);
}

static int	do_pipe(t_cmd *cmd, t_data *d)
{
	t_cmd	*next_cmd;

	next_cmd = cmd->next;
	if (next_cmd && next_cmd->argv[0]) // if true, pipe exists
	{
		d->pipe_exists = 1;
		if (pipe(d->pipe_fd) < 0)
			return (global_error(d));
		d->backup.old_fd_in = d->pipe_fd[0];
		if (next_cmd->fd_in == 0)
			next_cmd->fd_in = d->pipe_fd[0];
		else
			if (close(d->pipe_fd[0]) < 0)
				return (global_error(d));
		if (cmd->fd_out == 1)
			cmd->fd_out = d->pipe_fd[1];
		else
			if (close(d->pipe_fd[1]) < 0)
				return (global_error(d));
	}
	return (0);
}

static int	wait_loop(t_data *d, t_cmd *cmd)
{
	int	status;

	while (cmd)
	{
		if (cmd->pid)
		{
			if (waitpid(cmd->pid, &status, 0) < 0)
				return (global_error(d));
			d->status_code = WEXITSTATUS(status);
		}
		cmd = cmd->next;
	}
	return (0);
}

static int	core_loop(t_cmd *cmd, t_data *d) // segfault: ls > out | > 3
{
	while (cmd)
	{



		cmd->pid = 0;
		if (dup2(cmd->fd_in, 0) < 0) // init has to be on 0
			return (global_error(d));
		if (cmd->fd_in)
			if (close(cmd->fd_in) < 0)
				return (global_error(d));

		if (do_pipe(cmd, d))
			return (1);

		// if (!d->pipe_exists)
			if (dup2(d->backup.fd_out, 1) < 0)
				return (global_error(d));

		if (dup2(cmd->fd_out, 1) < 0) // init has to be on 1
			return (global_error(d));
		if (cmd->fd_out != 1)
			if (close(cmd->fd_out) < 0)
				return (global_error(d));

		if (cmd->argv[0])
			if (execute(cmd, d))
				return (1);

		if (dup2(d->backup.fd_in, 0) < 0)
				return (global_error(d)); // hmmmmmm

		// if (close(d->pipe_fd[1]) < 0)
		// 	return (global_error(d)); //hmmm
		// if (close(d->backup.old_fd_in) < 0)
		// 	return (global_error(d)); //hmmm
		cmd = cmd->next;
	}
	return (0);
}

int	executor(t_cmd *cmd, t_data *d)
{
	t_cmd	*cmd_cpy;

	cmd_cpy = cmd;
	d->pipe_exists = 0;
	if (core_loop(cmd, d))
		return (1);
	
			
	// if (d->pipe_fd[1] != -1)
	// 	if (close(d->pipe_fd[1]) < 0)
	// 		return (global_error(d)); // about this
	
	if (wait_loop(d, cmd_cpy))
		return (1);
	return (0);
}
