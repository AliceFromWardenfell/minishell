#include "minishell.h"

int is_key(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	key_length(t_char *no_q)
{
	int	i;

	i = 1;
	if (no_q[i].c == '?' && no_q[i].escaped == no_q[0].escaped)
		return (2);
	else
		while(is_key(no_q[i].c) && no_q[i].escaped == no_q[0].escaped)
			i++;
	return (i);
}

void *free_return_null(void *to_free)
{
	free(to_free);
	return (NULL);
}

int	tchar_strlen(t_char *str)
{
	int	i;
	
	i = 0;
	while(str[i].c)
		i++;
	return (i);
}

t_char	*tchardup(t_char *str)
{
	t_char	*res;
	int		i;

	res = (t_char *)malloc(sizeof(t_char) * (tchar_strlen(str) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i].c)
	{	
		ft_charcpy(&res[i], str[i].c, str[i].escaped);
		i++;
	}
	ft_charcpy(&res[i], '\0', -1);
	return (res);
}
