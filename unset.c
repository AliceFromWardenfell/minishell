#include "executor.h"

int	unset_b(t_cmd *cmd, t_data *d)
{
	int		i;
	char	*argv_cpy;
	char	*eq_pos;
	int		line_to_del;

	i = 0;
	line_to_del = -1;
	while (cmd->argv[++i])
	{
		argv_cpy = ft_strdup(cmd->argv[i]);
		eq_pos = ft_strchr(argv_cpy, '=');
		if (eq_pos)
			eq_pos[1] = '\0';
		if (eq_pos && key_exist(d, argv_cpy, &line_to_del))
			ret_status = replace_line(cmd, d, line_to_replace, i);
		else if (eq_pos && !key_exist(d, argv_cpy, &line_to_replace))
			ret_status = add_line(cmd, d, i);
		free(argv_cpy);
	}
	return (0);
}