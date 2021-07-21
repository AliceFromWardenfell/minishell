#include "minishell.h"

static int	do_fork(t_cmd *cmd, t_data *d)
{
	char	*path_to_exec;

	path_to_exec = ft_strrchr(cmd->argv[0], '/');
	if (!path_to_exec)
		path_to_exec = cmd->argv[0];
	else
		path_to_exec++;
	
	if (!has_slash(cmd->argv[0]))
		path_to_exec = search_for_exec(d, path_to_exec); //handle errors
	if (!path_to_exec)
		return (global_error(d));
	

	
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (global_error(d));
	if (!cmd->pid)
		if (execve(path_to_exec, cmd->argv, d->env) < 0)
		{
			
			free(path_to_exec); // mb move to global_error
			exit(global_error(d));
		}
	free(path_to_exec);
	// if (pid)
	// {
	// 	signal(SIGINT, SIG_DFL);
	// 	signal(SIGQUIT, SIG_DFL);
	// }

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
		do_builtin(cmd, d, builtin);
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

static int	core_loop(t_cmd *cmd, t_data *d)
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

int	executor(t_cmd *cmd, t_data *d)
{
	t_cmd	*cmd_cpy;

	cmd_cpy = cmd;
	if (core_loop(cmd, d))
		return (1);
	if (wait_loop(d, cmd_cpy))
		return (1);
	printf("status_code: %d\n", d->status_code); // remove
	return (0);
}
