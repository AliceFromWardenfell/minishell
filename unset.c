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

int	unset_b(t_cmd *cmd, t_data *d) //add prot from non-format
{
	int		i;
	char	*argv_cpy;
	int		line_to_del;

	i = 0;
	line_to_del = -1;
	while (cmd->argv[++i])
	{
		argv_cpy = ft_strjoin(cmd->argv[i], "=");
		if (!argv_cpy)
			return (builtin_error("unset", NULL, NULL));
		if (key_exist(d, argv_cpy, &line_to_del))
			remove_line(d, line_to_del);
		free(argv_cpy);
	}
	return (0);
}