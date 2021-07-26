#include "minishell.h"

int	dup_envp(t_data *d, const char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	d->env = (char **)malloc((i + 1) * sizeof(char *));
	if (!d->env)
		return (global_error(d));
	i = -1;
	while (envp[++i])
	{
		d->amount_of_alloc_lines = i;
		d->env[i] = (char *)malloc((ft_strlen(envp[i]) + 1) * sizeof(char)); //strlen has to be protected (not really)
		if (!d->env[i])
			return (global_error(d));
		ft_strlcpy(d->env[i], envp[i], ft_strlen(envp[i]) + 1);
	}
	d->env[i] = NULL;
	d->amount_of_alloc_lines++;
	return (0);
}

int	get_env_val(t_data *d, char *key, char **val)
{
	int		i;

	*val = NULL;
	i = -1;
	while (d->env[++i])
	{
		if (!ft_strncmp(key, d->env[i], ft_strlen(key)))
		{
			*val = ft_strdup(&(d->env[i][ft_strlen(key)]));
			if (!*val)
				return (1); // MALLOC ERROR
			// *val = &(d->env[i][ft_strlen(key)]);
			return (0);
		}
	}
	return (0);
}

int	change_env_val(t_data *d, char *key, char *val)
{
	int		i;
	char	*new_line;
	char	*old_line;

	new_line = ft_strjoin(key, val);
	if (!new_line)
		return (1); // MALLOC ERROR
	i = -1;
	while (d->env[++i])
	{
		if (!ft_strncmp(key, d->env[i], ft_strlen(key)))
		{
			old_line = d->env[i];
			d->env[i] = new_line;
			free(old_line);
			return (0);
		}
	}
	return (0);
}
