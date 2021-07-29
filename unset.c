#include "minishell.h"

static void	remove_line(t_data *d, int i)
{
	d->amount_of_alloc_lines--;
	if (d->amount_of_alloc_lines != i)
		free(d->env[i]);
	d->env[i] = d->env[d->amount_of_alloc_lines];
	if (d->amount_of_alloc_lines == i)
		free(d->env[d->amount_of_alloc_lines]);
	d->env[d->amount_of_alloc_lines] = NULL;
}

int	unset_key_error(int *flag)
{
	*flag = 1;
	printf("minishell: unset: not a valid identifier\n");
	return (1);
}

static int	check_key(char *argv_cpy, int *flag)
{
	int		i;

	if (!ft_isalpha(argv_cpy[0]) && argv_cpy[0] != '_')
		return (unset_key_error(flag));
	i = 0;
	while (argv_cpy[++i] != '=')
		if (!(ft_isalnum(argv_cpy[i]) || argv_cpy[i] == '_'))
			return (unset_key_error(flag));
	if (argv_cpy[++i] != '\0')
		return (unset_key_error(flag));
	return (0);
}

int	unset_b(t_cmd *cmd, t_data *d)
{
	int		i;
	char	*argv_cpy;
	int		line_to_del;
	int		check_key_failed;
	
	i = 0;
	line_to_del = -1;
	check_key_failed = 0;
	while (cmd->argv[++i])
	{
		argv_cpy = ft_strjoin(cmd->argv[i], "=");
		if (!argv_cpy)
			return (builtin_error("unset", NULL, NULL));
		if (!check_key(argv_cpy, &check_key_failed))
		{
			if (key_exist(d, argv_cpy, &line_to_del))
				remove_line(d, line_to_del);
		}
		free(argv_cpy);
	}
	if (check_key_failed)
		return (check_key_failed);
	return (0);
}
