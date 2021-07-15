#include "minishell.h"

void	*array_clear(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
		free(ar[i++]);
	free(ar);
	return (NULL);
}

static int	word_count(t_char *no_q)
{
	int	res;
	int	flag;

	res = 0;
	flag = 0;
	while (no_q->c)
	{
		if (!ft_is_blank(no_q) && flag == 0)
		{
			res++;
			flag = 1;
		}
		else if (ft_is_blank(no_q) && flag == 1)
			flag = 0;
		no_q++;
	}
	return (res);
}

static char	*ft_get_word(t_char *no_q)
{
	char	*res;
	int		i;

	res = (char *)malloc(sizeof(char) * (get_word_size(no_q) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (no_q->c && !ft_is_blank(no_q))
	{	
		if (no_q->c != -1)
			res[i++] = no_q->c;
		no_q++;
	}
	res[i] = '\0';
	return (res);
}

char	**lexer(t_char *no_q)
{
	char	**res;
	int		flag;
	int		i;

	res = (char **)malloc(sizeof(char *) * (word_count(no_q) + 1));
	if (!res)
		return (NULL);
	flag = 0;
	i = 0;
	while (no_q->c)
	{
		if (!ft_is_blank(no_q) && flag == 0)
		{
			res[i] = ft_get_word(no_q);
			if (!res[i++])
				return (array_clear(res));
			flag = 1;
		}
		else if (ft_is_blank(no_q) && flag == 1)
			flag = 0;
		no_q++;
	}
	res[i] = NULL;
	return (res);
}
