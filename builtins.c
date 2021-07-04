#include "executor.h"

int		do_builtin(t_cmd *cmd, int builtin)
{
	int		ret;

	ret = 0;
	if (builtin == ECHO)
		ret = echo_b(cmd);
	// if (builtin == CD)
	// 	ret = cd_b();
	// if (builtin == PWD)
	// 	ret = pwd_b();
	// if (builtin == EXPORT)
	// 	ret = export_b();
	// if (builtin == UNSET)
	// 	ret = unset_b();
	// if (builtin == ENV)
	// 	ret = env_b();
	// if (builtin == EXIT)
	// 	ret = exit_b();
	return (ret);
}

int		is_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return(ECHO);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return(CD);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return(PWD);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return(EXPORT);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return(UNSET);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return(ENV);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return(EXIT);
	return (0);
}