#include "executor.h"

int		change_env_val(t_data *d, char *key, char *val)
{
	int		i;
	char	*new_line;
	char	*old_line;

	new_line = ft_strjoin(key, val); // probably need to add \n at the end
	if (!new_line)
		return(1); // ERROR
	i = -1;
	while(d->env[++i])
	{
		if (!ft_strncmp(key, d->env[i], ft_strlen(key)))
		{
			old_line = d->env[i];
			d->env[i] = new_line;
			free(old_line);
			return(0);
		}
	}
	return (0);
}
