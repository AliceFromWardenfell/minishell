#include "minishell.h"
#include <unistd.h>

static t_cmd	*new_cmd(char **argv, int fd_in, int fd_out)
{
	t_cmd	*res;

	res = (t_cmd *)malloc(sizeof(t_cmd));
	if (!res)
		return (NULL);
	res->argv = argv;
	res->fd_in = fd_in;
	res->fd_out = fd_out;
	res->next = NULL;
	return (res);
}

static int	add_cmd(t_cmd **start, t_pipe *add)
{
	t_cmd *temp;
	char	**to_add;

	to_add = lexer(add->no_quote);
	if (!to_add)
		return (0);
	if (!*start)
	{
		*start = new_cmd(to_add, add->fd_in, add->fd_out);
		if (!*start)
			return (0);
		return (1);
	}
	temp = *start;
	while (temp->next)
		temp = temp->next;
	temp->next = new_cmd(to_add, add->fd_in, add->fd_out);
	if (!temp->next)
		return (0);
	return (1);
}

void	cmd_clear(t_cmd *start)
{
	t_cmd	*temp;
	t_cmd	*del;

	temp = start;
	while (temp)
	{
		del = temp;
		temp = temp->next;
		array_clear(del->argv);
		if (del->fd_in != 0)
			close(del->fd_in);
		if (del->fd_out != 1)
			close(del->fd_out);
		free(del);
	}
}

t_cmd *create_cmd(t_pipe *no_p)
{
	int			i;
	t_cmd	*res;

	i = 0;
	res = NULL;
	while (no_p[i].no_quote)
	{
		if (!add_cmd(&res, &no_p[i]))
		{
			cmd_clear(res);
			pipe_clear(no_p);
			return (NULL);
		}
		i++;
	}
	pipe_clear(no_p);
	return (res);
}
