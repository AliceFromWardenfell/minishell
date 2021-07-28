#include "minishell.h"

static int	handle_fdin(t_cmd *cmd, t_data *d, int *fd_in)
{
	if (cmd->fd_in)
		*fd_in = cmd->fd_in;
	else if (d->pipe_fd[0] == -1)
		*fd_in = cmd->fd_in;
	if (dup2(*fd_in, 0) < 0)
		return (global_error(d));
	if (d->pipe_fd[0] != -1)
	{
		if (close(d->pipe_fd[0]) < 0)
			return (global_error(d));
		d->pipe_fd[0] = -1;
	}
	return (0);
}

static int	handle_fdout(t_cmd *cmd, t_data *d, int *fd_out)
{
	if (cmd->fd_out != 1)
		*fd_out = cmd->fd_out;
	else if (d->pipe_fd[1] == -1)
		*fd_out = cmd->fd_out;
	if (dup2(*fd_out, 1) < 0)
		return (global_error(d));
	if (d->pipe_fd[1] != -1)
	{
		if (close(d->pipe_fd[1]) < 0)
			return (global_error(d));
		d->pipe_fd[1] = -1;
	}
	return (0);
}

static int	execute(t_cmd *cmd, t_data *d)
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
			do_builtin(cmd, d, builtin);
			exit(d->status_code);
		}
	}
	return (0);
}

static int	core_loop(t_cmd *cmd, t_data *d)
{
	int		fd_in;
	int		fd_out;

	fd_in = 0;
	fd_out = 1;
	while (cmd)
	{
		cmd->pid = 0;
		if (handle_fdin(cmd, d, &fd_in))
			return (1);
		if (do_pipe(cmd, d, &fd_in, &fd_out))
			return (1);
		if (handle_fdout(cmd, d, &fd_out))
			return (1);
		if (cmd->argv[0])
			if (execute(cmd, d))
				return (1);
		if (fd_restore(d))
			return (1);
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
	if (wait_loop(d, cmd_cpy))
		return (1);
	return (0);
}
