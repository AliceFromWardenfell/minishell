#include "executor.h"

int		cd_b(t_cmd *cmd, t_data *d)
{
	int		argc;

	argc = 0;
	if (!d->env)
		printf("Unused parametr now used!\n"); //remove ofc
	while (cmd->argv[argc])
		argc++;
	if (argc > 2)
		printf("minishell: cd: слишком много аргументов\n");
	if (argc == 1)
		if (chdir("~")) // change this on env var (because this dosn't even work lol)
		{
			printf("%s\n", strerror(errno)); //simulate error on stdout
			return (0);
		}
	if (argc == 2)
		if (chdir(cmd->argv[1]))
		{
			printf("%s\n", strerror(errno));
			return (0);
		}
	open("CD_WORKS PROPERLY", O_RDONLY | O_CREAT);
	return (0);
}