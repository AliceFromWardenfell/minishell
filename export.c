#include "minishell.h"

int	key_exist(t_data *d, char *key, int	*line_num)
{
	int		i;
	int		key_len;

	key_len = ft_strlen(key);
	i = -1;
	while (d->env[++i])
	{	
		if (!strncmp(d->env[i], key, key_len))
		{
			*line_num = i;
			return (1);
		}
	}
	return (0);
}

static int	replace_line(t_cmd *cmd, t_data *d,
						int line_to_replace, int argv_num)
{
	char	*old_line;
	char	*new_line;

	old_line = d->env[line_to_replace];
	new_line = ft_strdup(cmd->argv[argv_num]);
	if (!new_line)
		return (builtin_error("export", NULL, NULL)); // MALLOC ERROR
	d->env[line_to_replace] = new_line;
	free(old_line);
	return (0);
}

static int	add_line(t_cmd *cmd, t_data *d, int argv_num)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (d->env[i])
		i++;
	new_arr = (char **)malloc((i + 2) * sizeof(char *));
	if (!new_arr)
		return (builtin_error("export", NULL, NULL));
	i = -1;
	while (d->env[++i])
	{
		new_arr[i] = ft_strdup(d->env[i]);
		if (!new_arr[i])
		{
			while (--i >= 0)
				free(new_arr[i]);
			free(new_arr);
			return (builtin_error("export", NULL, NULL));
		}
	}
	new_arr[i] = ft_strdup(cmd->argv[argv_num]);
	new_arr[++i] = NULL;
	d->amount_of_alloc_lines++;
	clean(d);
	d->env = new_arr;
	return (0);
}

static int	check_key(char *argv_cpy, const char *eq_pos, int *flag)
{
	int		i;
	int		len;

	len = ft_strlen(argv_cpy);
	if (eq_pos) //return (builtin_error("export", argv_cpy, NULL));
	{
		if (!ft_isalpha(argv_cpy[0]) && argv_cpy[0] != '_')
			return (export_key_error(flag));
		i = 0;
		while (++i < len)
			if (!(ft_isalnum(argv_cpy[i]) || argv_cpy[0] == '_'))
				return (export_key_error(flag));
	}
	return (0);
}

int	export_b(t_cmd *cmd, t_data *d)
{
	int		i;
	char	*argv_cpy;
	char	*eq_pos;
	int		ret_status;
	int		line_to_replace;
	int		check_key_failed;
	
	i = 0;
	ret_status = 0;
	line_to_replace = -1;
	check_key_failed = 0;
	while (cmd->argv[++i])
	{
		argv_cpy = ft_strdup(cmd->argv[i]);
		eq_pos = ft_strchr(argv_cpy, '=');
		if (eq_pos)
			eq_pos[1] = '\0';
		if (!check_key(argv_cpy, eq_pos, &check_key_failed))
		{	
			if (eq_pos && key_exist(d, argv_cpy, &line_to_replace))
				ret_status = replace_line(cmd, d, line_to_replace, i);
			else if (eq_pos && !key_exist(d, argv_cpy, &line_to_replace))
				ret_status = add_line(cmd, d, i);
		}
		free(argv_cpy);
		if (ret_status)
			return (ret_status);
	}
	if (check_key_failed)
		return (check_key_failed);
	return (0);
}
