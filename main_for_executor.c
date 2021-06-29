#include "executor.h"

int		main(void)
{
	t_cmd	cmd1;
	t_cmd	cmd2;
	t_cmd	cmd3;

	cmd3.next = NULL;
	cmd2.next = &cmd3;
	cmd1.next = &cmd2;

	cmd1.argv = (char **)malloc(4 * sizeof(char*));
	cmd1.argv[0] = "subtr";
	cmd1.argv[1] = NULL;
	cmd1.fd_out	= 1;
	cmd1.fd_in	= open("input", O_RDONLY, 0644);
	
	cmd2.argv = (char **)malloc(4 * sizeof(char*));
	cmd2.argv[0] = "pow2";
	cmd2.argv[1] = NULL;
	cmd2.fd_out = 1;
	cmd2.fd_in = 0;

	cmd3.argv = (char **)malloc(4 * sizeof(char*));
	cmd3.argv[0] = "plus5";
	cmd3.argv[1] = NULL;
	cmd3.fd_out	= open("output", O_WRONLY | O_CREAT, 0644);
	cmd3.fd_in	= 0;

	executor(&cmd1);

	return (0);
}