#include "minishell.h"

int ft_is_blank(t_char *c)
{
	if ((c->c == ' ' || c->c == '\n' || c->c == '\t') && c->escaped == 0)
		return (1);
	return (0);
}

int	pipe_check(t_char *no_quote)
{
	int	flag;
	int	pipe;
	int i;

	i = 0;
	flag = 0;
	pipe = 0;
	while (no_quote[i].c != '\0')
	{
		if (!(no_quote[i].c == '|' && no_quote[i].escaped == 0)
			&& !ft_is_blank(&no_quote[i]))
			flag = 1;
		else if (no_quote[i].c == '|' && no_quote[i].escaped == 0 && flag == 0)
			return (free_return_int(no_quote, 0));
		else if (no_quote[i].c == '|' && no_quote[i].escaped == 0 && flag == 1)
		{
			pipe = 1;
			flag = 0;
		}
		i++;
	}
	if (flag == 0 && pipe == 1)
		return (free_return_int(no_quote, 0));
	return (1);
}
