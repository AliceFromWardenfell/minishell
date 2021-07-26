#include "minishell.h"

void	print_2d(char **arr) //tmp func
{
	int		i;

	i = -1;
	while (arr[++i])
		printf("%d. %s\n", i, arr[i]);
}

void	init(t_data *d)
{
	errno = 0;
	d->env = NULL;
	d->amount_of_alloc_lines = 0;
	d->backup.fd_out = -1;
	d->backup.fd_in = -1;
	d->backup.old_fd_in = -1;
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
