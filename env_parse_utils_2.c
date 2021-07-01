#include "minishell.h"

int	key_check(t_char *no_q)
{
	if (no_q->c == '$' && no_q->escaped != 2
		&& ((no_q->escaped == (no_q + 1)->escaped
		&& (ft_isalpha((no_q + 1)->c) || (no_q + 1)->c == '_'
		|| (no_q + 1)->c == '?')) || (no_q->escaped == 0
		&& ((no_q + 1)->escaped == 1 || (no_q + 1)->c == -1))))
		return (1);
	return (0);
}

int	env_parse(t_pipe *no_p, char **env)
{
	t_char	*temp;
	int		i;

	i = 0;
	while (no_p[i].no_quote)
	{
		temp = check_env(no_p[i].no_quote, env);
		if (!temp)
		{
			pipe_clear(no_p);
			return (0);
		}
		no_p[i].no_quote = temp;
		i++;
	}
	return (1);
}