#include "executor.h"

void	print_2d(char **arr) //tmp func
{
	int		i;

	i = -1;
	while (arr[++i])
		printf("%s\n", arr[i]);
}

int	dup_envp(t_data *d, const char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	d->env = (char **)malloc((i + 1) * sizeof(char *));
	if (!d->env)
		return(global_error(d));
	i = -1;
	while (envp[++i])
	{
		d->amount_of_alloc_lines = i;
		d->env[i] = (char *)malloc((ft_strlen(envp[i]) + 1) * sizeof(char)); //strlen has to be protected
		if (!d->env[i])
			return(global_error(d));
		ft_strlcpy(d->env[i], envp[i], ft_strlen(envp[i]) + 1);
	}
	d->env[i] = NULL;
	return(0);
}
