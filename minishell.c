#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

int	main (int argc, char **argv, char **env)
{
	char	*str;
	t_cmd	*cmd;
	t_cmd	*tmp;
	int		i;
	int		id;

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
		tmp = cmd;
		id = 0;
		signal(SIGINT, SIG_IGN);
		if (tmp->argv[0] && !ft_strncmp(tmp->argv[0], "a.out", 5))
		{
			id = fork();
			if (id == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				execve("a.out", tmp->argv, env);
				exit(1);
			}
			else
				wait(NULL);
		}
		if (tmp->argv[0] && !ft_strncmp(tmp->argv[0], "cat", 3))
		{
			id = fork();
			if (id == 0)
			{	
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				execve("/bin/cat", tmp->argv, env);
				exit(1);
			}
			else if (id > 0)
				wait(NULL);
		}
		if (id > 0)
			printf("I'm a parent\n");
		while (tmp)
		{
			i = 0;
			while (tmp->argv[i])
				printf("%s\n", tmp->argv[i++]);
			printf("in:%d,  out:%d\n", tmp->fd_in, tmp->fd_out);
			tmp = tmp->next;
		}
		cmd_clear(cmd);
		free(str);
		signal(SIGINT, &sig_handler);
		str = readline("minishell> ");
	}
	return (0);
}
