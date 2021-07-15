#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>

int	main (int argc, char **argv, char **env)
{
	char	*str;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
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
		executor(cmd, (const char **)env); // check ret on errros
		cmd_clear(cmd);
		free(str);
		signal(SIGINT, &sig_handler);
		str = readline("minishell> ");
	}
	return (0);
}
