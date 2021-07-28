#include "minishell.h"

void	init(t_data *d)
{
	errno = 0;
	d->env = NULL;
	d->amount_of_alloc_lines = 0;
	d->backup.fd_out = -1;
	d->backup.fd_in = -1;
	d->backup.old_fd_in[0] = -1;
	d->backup.old_fd_in[1] = -1;
	d->status_code = 0;
	d->pipe_fd[0] = -1;
	d->pipe_fd[1] = -1;
}

void	clean_2d_arr(char **arr)
{
	int		i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
			free(arr[i]);
		free(arr);
	}
}

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
