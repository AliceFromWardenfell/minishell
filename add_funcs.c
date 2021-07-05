#include "executor.h"

char	**dup_envp(char **envp)
{
	int		i;
	
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return(0);
}