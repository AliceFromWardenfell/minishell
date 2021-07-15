#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	*print_r(char *to_print, void *to_return)
{
	ft_putstr_fd(to_print, 2);
	return (to_return);
}

static t_pipe	*parser_pipe(char *str)
{
	t_char	*no_quote;
	t_pipe	*no_pipe;

	if (!quote_check(str))
		return (print_r("Syntax error, quotes\n", NULL));
	no_quote = unquote(str);
	if (!no_quote)
		return (print_r("Malloc failed\n", NULL));
	if (!pipe_check(no_quote))
		return (print_r("Syntax error, pipe\n", NULL));
	no_pipe = piper(no_quote);
	free(no_quote);
	if (!no_pipe)
		return (print_r("Malloc failed\n", NULL));
	return (no_pipe);
}

t_cmd	*parser(char *str, char **env)
{
	t_pipe	*no_pipe;
	t_cmd	*cmd;

	if (!*str)
		return (NULL);
	add_history(str);
	no_pipe = parser_pipe(str);
	if (!no_pipe)
		return (NULL);
	if (!redirect_sycheck(no_pipe))
		return (print_r("Syntax error, redirection\n", pipe_clear(no_pipe)));
	if (!redirection_parse(no_pipe, env))
		return (NULL);
	if (!env_parse(no_pipe, env))
		return (print_r("Malloc failed\n", NULL));
	cmd = create_cmd(no_pipe);
	if (!cmd)
		return (print_r("Malloc failed\n", NULL));
	return (cmd);
}
