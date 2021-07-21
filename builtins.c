#include "minishell.h"

void	do_builtin(t_cmd *cmd, t_data *d, int builtin)
{
	int		ret;

	ret = 0;
	if (builtin == ECHO)
		ret = echo_b(cmd);
	if (builtin == CD)
		ret = cd_b(cmd, d);
	if (builtin == PWD)
		ret = pwd_b();
	if (builtin == EXPORT)
		ret = export_b(cmd, d);
	if (builtin == UNSET)
		ret = unset_b(cmd, d);
	if (builtin == ENV)
		ret = env_b(d);
	// if (builtin == EXIT)
	// 	ret = exit_b();
	d->status_code = ret;
}

int	is_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (ECHO);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (CD);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (PWD);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (EXPORT);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (UNSET);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (ENV);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (EXIT);
	return (0);
}
