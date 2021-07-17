#include "minishell.h"

int	remove_line(t_data *d, int i)
{

}

int	unset_b(t_cmd *cmd, t_data *d) //add prot from non-format
{
	int		i;
	char	*argv_cpy;
	char	*eq_pos;
	int		line_to_del;

	print_2d(d->env);
	
	i = 0;
	line_to_del = -1;
	while (cmd->argv[++i])
	{
		argv_cpy = ft_strjoin(cmd->argv[i], "=");
		
		if (key_exist(d, argv_cpy, &line_to_del))
			remove_line(d, line_to_del);
		free(argv_cpy);
	}

	printf("\n********************\n\n");
	print_2d(d->env);

	return (0);
}