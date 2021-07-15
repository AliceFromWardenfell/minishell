#include "minishell.h"
#include <unistd.h>

void	*pipe_clear(t_pipe *no_pipe)
{
	int	i;

	i = 0;
	while (no_pipe[i].no_quote != NULL)
	{
		if (no_pipe[i].fd_in != 0)
			close (no_pipe[i].fd_in);
		if (no_pipe[i].fd_out != 1)
			close (no_pipe[i].fd_out);
		free(no_pipe[i].no_quote);
		i++;
	}
	free(no_pipe);
	return (NULL);
}

static int	pipe_count(t_char *no_quote)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (no_quote[i].c != '\0')
	{
		if (no_quote[i].c == '|' && no_quote[i].escaped == 0)
			res++;
		i++;
	}
	return (res);
}

void	ft_charcpy(t_char *to, char c, int escaped)
{
	to->c = c;
	to->escaped = escaped;
}

t_pipe	*piper(t_char *no_q)
{
	t_pipe	*res;
	int		i;

	res = (t_pipe *)malloc(sizeof(t_pipe) * (pipe_count(no_q) + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (no_q->c != '\0')
	{
		res[i].fd_in = 0;
		res[i].fd_out = 1;
		res[i].no_quote = tpipe_fill(&no_q);
		if (res[i++].no_quote == NULL)
			return (pipe_clear(res));
	}
	res[i].no_quote = NULL;
	return (res);
}
