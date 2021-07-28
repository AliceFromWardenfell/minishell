#include "minishell.h"

static int	has_slash(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == '/')
			return (1);
	return (0);
}

static int	in_child(t_cmd *cmd, t_data *d,
					int was_allocation, char *path_to_exec)
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
			free(path_to_exec);
		exit(global_error(d));
	}
	return (0);
}

int	do_fork(t_cmd *cmd, t_data *d)
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
		if (in_child(cmd, d, was_allocation, path_to_exec))
			return (1);
	if (was_allocation)
		free(path_to_exec);
	return (0);
}
