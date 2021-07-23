#include "minishell.h"

static int	fd_backup(t_data *d)
{
	d->backup.fd_out = dup(1);
	if (d->backup.fd_out < 0)
		return (global_error(d));
	d->backup.fd_in = dup(0);
	if (d->backup.fd_in < 0)
		return (global_error(d));
	return (0);
}

static int 	fd_restore(t_data *d)
{
	if (dup2(d->backup.fd_out, 1) < 0)
		return (global_error(d));
	if (close(d->backup.fd_out) < 0)
		return (global_error(d));
	if (dup2(d->backup.fd_in, 0) < 0)
		return (global_error(d));
	if (close(d->backup.fd_in) < 0)
		return (global_error(d));
	return (0);
}

int	main (int argc, char **argv, char **env)
{
	char	*str;
	t_cmd	*cmd;
	t_data	d;

	(void)argc; // mv to init
	(void)argv;
	
	init(&d);
	if (dup_envp(&d, (const char **)env))
		return (1);
	if (fd_backup(&d))
		return (1);
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
		if (fd_restore(&d))
			return (1);
		str = readline("minishell> ");
	}
	clean(&d);
	return (0);
}
