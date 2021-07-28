#include "minishell.h"

static void	is_num(char *str)
{
	int		i;
	
	i = 0;
	if (str && ft_strlen(str) > 1 && (str[0] == '+' || str[0] == '-') && ft_isdigit(str[1]))
		while (str[++i])
			if (!ft_isdigit(str[i]))
				exit(2);
	if (str && ft_strlen(str) > 1 && (str[0] == '+' || str[0] == '-') && !ft_isdigit(str[1]))
		exit(2);
}

static int	check_arg(char *str)
{
	int		n;

	is_num(str);
	n = ft_atoi(str);
	if (n <= 0 || n >= 255)
		exit(255);
	return (n);
}

void	exit_b(t_cmd *cmd, t_data *d)
{
	fd_restore(d);
	fd_close(d);
	if (!d->pipe_exists)
		ft_putstr_fd("exit\n", 1);
	if (cmd->argv[1])
		exit(check_arg(cmd->argv[1]));
	else
		exit(d->status_code);
}
