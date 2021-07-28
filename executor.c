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
	if (has_slash(cmd->argv[0]) && cmd->argv[0][0] != '/')
		path_to_exec = cmd->argv[0];
	else if (!has_slash(cmd->argv[0]))
		path_to_exec = search_for_exec(d, path_to_exec, &was_allocation);
	if (!path_to_exec)
		return (global_error(d));
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (global_error(d));
	if (!cmd->pid)
	{
		if (d->pipe_fd[1] != -1)
			if (close(d->pipe_fd[1]) < 0)
				return (global_error(d));
		if (d->pipe_fd[0] != -1)
			if (close(d->pipe_fd[0]) < 0)
				return (global_error(d));
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

static int	do_pipe(t_cmd *cmd, t_data *d, int *fd_in, int * fd_out)
{
	t_cmd	*next_cmd;

	next_cmd = cmd->next;
	if (next_cmd && next_cmd->argv[0]) // if true, pipe exists
	{
		d->pipe_exists = 1;
		if (pipe(d->pipe_fd) < 0)
			return (global_error(d));
		*fd_in = d->pipe_fd[0];
		*fd_out = d->pipe_fd[1];
	}
	return (0);
}

static int	wait_loop(t_data *d, t_cmd *cmd)
{
	int	status;
	int	sig_num;

	while (cmd)
	{
		if (cmd->pid)
		{
			if (waitpid(cmd->pid, &status, 0) < 0)
				return (global_error(d));
			if (WIFSIGNALED(status))
			{
				sig_num = WTERMSIG(status);
				if (sig_num == SIGINT)
					ft_putchar('\n');
				else if (sig_num == SIGQUIT)
					ft_putstr("Quit (core dumped)\n");
				d->status_code = 128 + sig_num;
			}
			else
				d->status_code = WEXITSTATUS(status);
		}
		cmd = cmd->next;
	}
	return (0);
}

// int		input_file_exists(t_cmd *cmd)
// {
// 	while (cmd)
// 	{
// 		if (cmd->fd_in != 0)
// 			return (cmd->fd_in);
// 		cmd = cmd->next;
// 	}
	
// 	return (0);
// }

static int	core_loop(t_cmd *cmd, t_data *d) // segfault: ls > out | > 3
{
	int		fd_in;
	int		fd_out;

	fd_in = 0;
	fd_out = 1;
	while (cmd)
	{
		cmd->pid = 0;
		
		if (cmd->fd_in) // infile exists 
		{
			fd_in = cmd->fd_in; // if fd_in was pipe_fd[0], last one still unclosed
		}
		else if (d->pipe_fd[0] == -1)
			fd_in = cmd->fd_in; // no pipe


		if (dup2(fd_in, 0) < 0)
			return (global_error(d));
		
		// can close pipe_fd[0] here in case of not going to upper ifs, bec its still OPEN
		if (d->pipe_fd[0] != -1)
		{
			if (close(d->pipe_fd[0]) < 0)
				return (global_error(d));
			d->pipe_fd[0] = -1;
		}

		if (do_pipe(cmd, d, &fd_in, &fd_out))
			return (1);

		if (cmd->fd_out != 1) //outfile exists
		{
			fd_out = cmd->fd_out; // cat be still open pipe_fd[1]
		}
		else if (d->pipe_fd[1] == -1)
			fd_out = cmd->fd_out; // no pipe

		if (dup2(fd_out, 1) < 0)
			return (global_error(d));

		// can close pipe_fd[1] here in case of not going to upper ifs, bec its still OPEN
		if (d->pipe_fd[1] != -1)
		{
			if (close(d->pipe_fd[1]) < 0)
				return (global_error(d));
			d->pipe_fd[1] = -1;
		}
		
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
	// if (d->pipe_fd[1] != -1)
	// 	if (close(d->pipe_fd[1]) < 0)
	// 		return (global_error(d)); // about this
	if (wait_loop(d, cmd_cpy))
		return (1);
	return (0);
}
