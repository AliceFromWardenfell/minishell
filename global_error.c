#include "minishell.h"

int	export_key_error(int *flag)
{
	*flag = 1;
	printf("minishell: export: not a valid identifier\n");
	return (1);
}

int	builtin_error(char *builtin, char *to_free1, char *to_free2)
{
	if (to_free1)
		free(to_free1);
	if (to_free2)
		free(to_free2);
	printf("minishell: %s: %s\n", builtin, strerror(errno)); // add check whether or not errno == 0 before print //simulate error on stdout to see if syntax like in bash
	return (1);
}

void	clean(t_data *d)
{
	int		i;

	i = -1;
	while (++i < d->amount_of_alloc_lines)
		free(d->env[i]);
	if (d->env) //has to be init on NULL
		free(d->env);
}

int	global_error(t_data *d)
{
	if (d->backup.fd_out != -1)
	{
		if (dup2(d->backup.fd_out, 1) < 0)
			exit(1);
		if (close(d->backup.fd_out) < 0)
			exit(1);
	}
	if (d->backup.fd_in != -1)
	{
		if (dup2(d->backup.fd_in, 0) < 0)
			exit(1);
		if (close(d->backup.fd_in) < 0)
			exit(1);
	}
	printf("minishell: %s\n", strerror(errno)); // add check on wether or not errno == 0 before print
	return (1);
}
