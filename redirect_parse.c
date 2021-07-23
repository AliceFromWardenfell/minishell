#include "minishell.h"
#include <string.h>
#include <errno.h>

static int	get_redir(t_char *no_quote, int i)
{
	if (no_quote[i].c == '>' && no_quote[i].escaped == 0)
	{
		if (no_quote[i + 1].c == '>' && no_quote[i + 1].escaped == 0)
			return (2);
		else
			return (1);
	}
	else
	{
		if (no_quote[i + 1].c == '<' && no_quote[i + 1].escaped == 0)
			return (4);
		else
			return (3);
	}
}

static int	redirection_check(t_char *no_q)
{
	unsigned char	flag;
	int				i;

	flag = 0;
	i = 0;
	while (no_q[i].c)
	{
		if (!ft_is_blank(&no_q[i]) && flag == 0)
			flag = 1;
		else if (ft_is_blank(&no_q[i]) && flag == 1)
			flag = 2;
		else if (!ft_is_blank(&no_q[i]) && flag == 2)
			flag = 3;
		i++;
	}
	if (!(flag == 1 || flag == 2))
	{	
		free(no_q);
		return (0);
	}
	return (1);
}

static int	redirection_process(t_pipe *no_p, int i, char **env, t_data *d)
{
	t_char	*temp;
	char	*c_temp;
	int		redir;
	int		j;

	redir = get_redir(no_p->no_quote, i);
	temp = redir_env(get_redir_path(no_p->no_quote, i), env, redir, d);
	if (!temp)
		return (0);
	if (!redirection_check(temp))
		return (-2);
	c_temp = ch_transform(temp);
	if (!c_temp)
		return (0);
	j = redirect_get(no_p, redir, c_temp);
	if (j < 1)
		return (j);
	temp = get_new_noq(no_p->no_quote, i);
	if (!temp)
		return (0);
	free(no_p->no_quote);
	no_p->no_quote = temp;
	return (1);
}

static int	redirection_get(t_pipe *no_p, char **env, t_data *d)
{
	int	i;
	int	j;

	i = 0;
	while (no_p->no_quote[i].c)
	{
		if ((no_p->no_quote[i].c == '<' || no_p->no_quote[i].c == '>')
			&& no_p->no_quote[i].escaped == 0)
		{	
			j = redirection_process(no_p, i, env, d);
			if (j < 1)
				return (j);
			i--;
		}
		i++;
	}
	return (1);
}

int	redirection_parse(t_pipe *no_p, char **env, t_data *d)
{
	int	i;
	int	j;

	i = 0;
	while (no_p[i].no_quote)
	{
		j = redirection_get(&no_p[i], env, d);
		if (j == 0)
		{
			ft_putstr_fd("Malloc failed\n", 2);
			pipe_clear(no_p);
			return (0);
		}
		else if (j == -2)
			ft_putstr_fd("Ambiguous redirect\n", 2);
		if (j < 0)
			ft_charcpy(&no_p[i].no_quote[0], '\0', -1);
		i++;
	}
	return (1);
}
