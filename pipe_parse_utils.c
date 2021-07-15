#include "minishell.h"

static int	count(t_char *no_quote)
{
	int	i;

	i = 0;
	while (no_quote[i].c != '\0'
		&& !(no_quote[i].c == '|' && no_quote[i].escaped == 0))
		i++;
	return (i);
}

t_char	*tpipe_fill(t_char **no_q)
{
	t_char	*res;
	int		j;

	res = (t_char *)malloc(sizeof(t_char) * (count(*(no_q)) + 1));
	if (!res)
		return (NULL);
	j = 0;
	while ((*no_q)->c != '\0' && !((*no_q)->c == '|' && (*no_q)->escaped == 0))
	{
		ft_charcpy(&(res[j++]), (*no_q)->c, (*no_q)->escaped);
		(*no_q)++;
	}
	if ((*no_q)->c == '|' && (*no_q)->escaped == 0)
		(*no_q)++;
	ft_charcpy(&(res[j]), '\0', -1);
	return (res);
}
