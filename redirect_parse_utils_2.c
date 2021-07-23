#include "minishell.h"

int	get_word_size(t_char *no_q)
{
	int	i;

	i = 0;
	while (no_q->c && ft_is_blank(no_q))
		no_q++;
	while (no_q->c && !ft_is_blank(no_q))
	{	
		if (no_q->c != -1)
			i++;
		no_q++;
	}
	return (i);
}

char	*ch_transform(t_char *no_q)
{
	char	*res;
	int		i;
	int		j;

	res = (char *)malloc(sizeof(char) * (get_word_size(no_q) + 1));
	if (!res)
		return (free_return_null(no_q));
	j = 0;
	i = 0;
	while (no_q[i].c && ft_is_blank(&no_q[i]))
		i++;
	while (no_q[i].c && !ft_is_blank(&no_q[i]))
	{	
		if (no_q[i].c != -1)
			res[j++] = no_q[i].c;
		i++;
	}
	res[j] = '\0';
	free(no_q);
	return (res);
}

t_char	*redir_env(t_char *no_q, char **env, int redir, t_data *d)
{
	t_char	*temp;

	if (no_q && redir != 4)
	{
		temp = check_env(no_q, env, d);
		if (!temp)
		{
			free(no_q);
			return (NULL);
		}
		free(no_q);
		return (temp);
	}
	return (no_q);
}
