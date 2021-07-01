#include "minishell.h"

static void flag_check(char c, unsigned char *flag)
{
	if (c == '\"' && !(*flag & 1) && !(*flag & 2))
		*flag = *flag | 1;
	else if (c == '\"' && (*flag & 1))
		*flag = *flag ^ 1;
	else if (c == '\'' && !(*flag & 1) && !(*flag & 2))
		*flag = *flag | 2;
	else if (c == '\'' && (*flag & 2))
		*flag = *flag ^ 2;
}

int quote_check(char *str)
{
	unsigned char	flag;

	flag = 0;
	while (*str)
	{
		flag_check(*str, &flag);
		str++;
	}
	if (flag != 0)
		return (0);
	return (1);
}

static int	quote_count(char *str)
{
	int				res;
	unsigned char	flag;

	res = 0;
	flag = 0;
	while (*str)
	{
		if ((*str == '\"' || *str == '\'') && flag == 0)
			res++;
		flag_check(*str, &flag);
		str++;
	}
	return (res);
}

static void	set_char(char c, t_char *ch, unsigned char flag)
{
	if ((c == '\"' && (flag & 1)) || (c == '\'' && (flag & 2)))
	{
		ch->c = -1;
		ch->escaped = -1;
	}
	else if (c == '$' && (flag & 2))
	{
		ch->c = c;
		ch->escaped = 2;
	}
	else if (flag != 0)
	{	
		ch->c = c;
		ch->escaped = 1;
	}
	else
	{
		ch->c = c;
		ch->escaped = 0;
	}
}

t_char	*unquote(char *str)
{
	t_char			*res;
	unsigned char	flag;
	size_t			i;

	res = (t_char *)malloc(sizeof(t_char) * (ft_strlen(str)
			- quote_count(str) + 1));
	if (!res)
		return (NULL);
	i = 0;
	flag = 0;
	while (*str)
	{
		if ((*str == '\"' || *str == '\'') && flag == 0)
			;
		else
			set_char(*str, &(res[i++]), flag);
		flag_check(*str, &flag);
		str++;
	}
	res[i].c = '\0';
	res[i].escaped = -1;
	return (res);
}
