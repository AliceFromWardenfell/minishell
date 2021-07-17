#include "minishell.h"

int	main (int argc, char **argv, char **env)
{
	char	*str;
	t_cmd	*cmd;
	t_data	d;

	(void)argc;
	(void)argv;
	
	errno = 0;
	init(&d);
	if (dup_envp(&d, (const char **)env))
		return (1);
	d.backup.fd_out = dup(1);
	if (d.backup.fd_out < 0)
		return (global_error(&d));
	d.backup.fd_in = dup(0);
	if (d.backup.fd_in < 0)
		return (global_error(&d));

	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
	str = readline("minishell> ");
	while (str)
	{
		if (!(cmd = parser(str, env)))
		{
			free(str);
			str = readline("minishell> ");
			continue ;
		}
		signal(SIGINT, SIG_IGN);
		executor(cmd, &d); // check ret on errros
		cmd_clear(cmd);
		free(str);
		signal(SIGINT, &sig_handler);
		str = readline("minishell> ");
	}
	//restore fds
	if (dup2(d.backup.fd_out, 1) < 0)
		return (global_error(&d));
	if (close(d.backup.fd_out) < 0)
		return (global_error(&d));
	if (dup2(d.backup.fd_in, 0) < 0)
		return (global_error(&d));
	if (close(d.backup.fd_in) < 0)
		return (global_error(&d));
	clean(&d);

	return (0);
}
