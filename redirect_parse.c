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

static int	redirection_process(t_pipe *no_p, int i, char **env)
{
	t_char	*temp;
	char	*c_temp;
	int		redir;

	redir = get_redir(no_p->no_quote, i);
	temp = get_redir_path(no_p->no_quote, i);
	if (!temp)
		return (0);
	if (redir != 4)
		temp = redir_env(temp, env);
	if (!temp)
		return (0);
	if (!redirection_check(temp))
		return (-1);
	c_temp = ch_transform(temp);
	if (!c_temp)
		return (0);
	if (!redirect_get(no_p, redir, c_temp))
		return (-2);
	temp = get_new_noq(no_p->no_quote, i);
	if (!temp)
		return (0);
	no_p->no_quote = temp;
	return (1);
}

static int redirection_get(t_pipe *no_p, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (no_p->no_quote[i].c)
	{
		if ((no_p->no_quote[i].c == '<' || no_p->no_quote[i].c == '>')
			&& no_p->no_quote[i].escaped == 0)
		{	
			j = redirection_process(no_p, i, env);
			if (j < 1)
				return (j);
			i--;
		}
		i++;
	}
	return (1);
}

int	redirection_parse(t_pipe *no_p, char **env)
{
	int	i;
	int	j;
	
	i = 0;
	while(no_p[i].no_quote)
	{
		j = redirection_get(&no_p[i], env);
		if (j == 0)
			ft_putstr_fd("Malloc failed\n", 2);
		else if (j == -1)
			ft_putstr_fd("Ambiguous redirect\n", 2);
		else if (j == -2)
		{	
			ft_putstr_fd(strerror(errno), 2);
			ft_putchar_fd('\n', 2);
		}
		if (j < 1)
		{	
			pipe_clear(no_p);
			return (0);
		}
		i++;
	}
	return (1);
}
