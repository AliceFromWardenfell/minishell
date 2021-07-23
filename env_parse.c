#include "minishell.h"

static char	*get_key(t_char *no_q)
{
	int		i;
	int		j;
	char	*res;

	i = 1;
	j = 0;
	res = (char *)malloc(sizeof(char) * key_length(no_q) + 1);
	if (!res)
		return (NULL);
	while (is_key(no_q[i].c) && no_q[i].escaped == no_q[0].escaped)
	{	
		res[j++] = no_q[i].c;
		i++;
	}
	res[j++] = '=';
	res[j] = '\0';
	return (res);
}

static char	*get_env(t_char *no_q, char **env, t_data *d)
{
	char	*res;
	char	*key;

	if (no_q[1].c == '?' && no_q[1].escaped == no_q[0].escaped)
		return (ft_exit_status(d));
	key = get_key(no_q);
	if (!key)
		return (NULL);
	while (*env)
	{
		if (!ft_strncmp(*env, key, ft_strlen(key)))
		{
			res = ft_substr(*env, ft_strlen(key),
					ft_strlen(&((*env)[ft_strlen(key)])));
			free(key);
			return (res);
		}
		env++;
	}
	free(key);
	return (ft_strdup(""));
}

static t_char	*t_transform(char *to_trans, t_char *no_q)
{
	t_char	*res;
	int		i;

	if (!to_trans)
		return (NULL);
	res = (t_char *)malloc(sizeof(t_char) * (ft_strlen(to_trans) + 1));
	if (!res)
		return (free_return_null(to_trans));
	i = 0;
	while (to_trans[i])
	{
		if ((to_trans[i] == ' ' || to_trans[i] == '\n' || to_trans[i] == '\t')
			&& no_q->escaped == 0)
			ft_charcpy(&res[i], to_trans[i], 0);
		else if (to_trans[i] == '$')
			ft_charcpy(&res[i], to_trans[i], 2);
		else
			ft_charcpy(&res[i], to_trans[i], 1);
		i++;
	}
	ft_charcpy(&res[i], '\0', -1);
	free(to_trans);
	return (res);
}

static t_char	*str_paste(t_char *no_q, int start, int end, char *to_paste)
{
	t_char	*res;
	t_char	*paste;
	int		i;
	int		j;

	paste = t_transform(to_paste, &no_q[start]);
	if (!paste)
		return (NULL);
	res = (t_char *)malloc(sizeof(t_char)
			* (start + tchar_strlen(paste) + tchar_strlen(&no_q[end]) + 1));
	if (!res)
		return (free_return_null(paste));
	i = -1;
	while (++i < start)
		ft_charcpy(&res[i], no_q[i].c, no_q[i].escaped);
	j = -1;
	while (paste[++j].c)
		ft_charcpy(&res[i++], paste[j].c, paste[j].escaped);
	end--;
	while (no_q[++end].c)
		ft_charcpy(&res[i++], no_q[end].c, no_q[end].escaped);
	ft_charcpy(&res[i], '\0', -1);
	free(paste);
	return (res);
}

t_char	*check_env(t_char *no_q, char **env, t_data *d)
{
	int			i;
	t_char		*res;
	t_char		*temp;

	i = 0;
	res = tchardup(no_q);
	if (!res)
		return (NULL);
	while (res[i].c)
	{
		if (key_check(&res[i]))
		{
			temp = str_paste(res, i, i + key_length(&res[i]),
					get_env(&res[i], env, d));
			free(res);
			if (!temp)
				return (NULL);
			res = temp;
			i--;
		}
		i++;
	}
	return (res);
}
