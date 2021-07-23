#include "minishell.h"

static int	check_arg(char *str)
{
	int		i;
	int		n;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			exit(128);
	n = ft_atoi(str);
	if (n <= 0 || n >= 255)
		exit(255);
	return (n);
}

void	exit_b(t_cmd *cmd, t_data *d)
{
	fd_restore(d);
	fd_close(d);
	ft_putstr_fd("exit\n", 1);
	if (cmd->argv[1])
		exit(check_arg(cmd->argv[1]));
	else
		exit(d->status_code);
}