#include "minishell.h"

int	do_pipe(t_cmd *cmd, t_data *d, int *fd_in, int *fd_out)
{
	t_cmd	*next_cmd;

	next_cmd = cmd->next;
	if (next_cmd && next_cmd->argv[0])
	{
		d->pipe_exists = 1;
		if (pipe(d->pipe_fd) < 0)
			return (global_error(d));
		*fd_in = d->pipe_fd[0];
		*fd_out = d->pipe_fd[1];
	}
	return (0);
}

int	wait_loop(t_data *d, t_cmd *cmd)
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
