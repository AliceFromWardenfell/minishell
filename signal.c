#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
