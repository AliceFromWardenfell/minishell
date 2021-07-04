#include "executor.h"

int		echo_b(t_cmd *cmd)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (cmd->argv[1] && !ft_strcmp(cmd->argv[1], "-n"))
	{
		n = 1;
		i++;
	}
	while (cmd->argv[++i])
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(" ");
		else if (!n)
			printf("\n");
	}
	return (0);
}