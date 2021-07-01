#include "minishell.h"

static int	ft_is_redir(t_char	*c)
{
	if ((c->c == '<' || c->c == '>') && c->escaped == 0)
		return (1);
	return (0);
}

t_char	*get_redir_path(t_char *no_quote, int i)
{
	int		j;
	t_char	*res;
	
	while (no_quote[i].c && ft_is_redir(&no_quote[i]))
		i++;
	while (no_quote[i].c && ft_is_blank(&no_quote[i]))
		i++;
	j = i;
	while (no_quote[j].c && !ft_is_redir(&no_quote[j])
		&& !ft_is_blank(&no_quote[j]))
		j++;
	res = (t_char *)malloc(sizeof(t_char) * (j - i + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (no_quote[i].c && !ft_is_redir(&no_quote[i])
		&& !ft_is_blank(&no_quote[i]))
	{	
		ft_charcpy(&res[j++], no_quote[i].c, no_quote[i].escaped);
		i++;
	}
	ft_charcpy(&res[j], '\0', -1);
	return (res);
}

static t_char	*tchar_cut(t_char *no_q, int start, int end)
{
	int		i;
	t_char	*res;

	i = end;
	while (no_q[i].c)
		i++;
	res = (t_char *)malloc(sizeof(t_char) * (i - (end - start) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < start)
	{	
		ft_charcpy(&res[i], no_q[i].c, no_q[i].escaped);
		i++;
	}
	while (no_q[end].c)
	{
		ft_charcpy(&res[i++], no_q[end].c, no_q[end].escaped);
		end++;
	}
	ft_charcpy(&res[i], '\0', -1);
	return (res);
}

t_char	*get_new_noq(t_char *no_quote, int i)
{
	int		j;
	
	j = i;
	while (ft_is_redir(&no_quote[j]))
		j++;
	while (ft_is_blank(&no_quote[j]))
		j++;
	while (no_quote[j].c && !ft_is_redir(&no_quote[j])
		&& !ft_is_blank(&no_quote[j]))
		j++;
	return (tchar_cut(no_quote, i, j));
}
