#include "minishell.h"

static int	is_redir(t_char *c, int *i)
{
	if (c->c == '<' && c->escaped == 0)
	{
		if ((c + 1)->c == '<' && (c + 1)->escaped == 0)
			(*i)++;
		return (1);
	}
	else if (c->c == '>' && c->escaped == 0)
	{
		if ((c + 1)->c == '>' && (c + 1)->escaped == 0)
			(*i)++;
		return (1);
	}
	return (0);
}

int	redirect_sycheck(t_pipe *no_pipe)
{
	int flag;
	int	i;

	flag = 0;
	while (no_pipe->no_quote)
	{
		i = 0;
		while (no_pipe->no_quote[i].c)
		{
			if (is_redir(&no_pipe->no_quote[i], &i) && flag == 0)
				flag = 1;
			else if (is_redir(&no_pipe->no_quote[i], &i) && flag == 1)
				return (0);
			else if (!ft_is_blank(&no_pipe->no_quote[i]))
				flag = 0;
			i++;
		}
		if (flag == 1)
			return (0);
		no_pipe++;
	}
	return (1);
}
