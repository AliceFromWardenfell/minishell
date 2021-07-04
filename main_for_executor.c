#include "executor.h"

int		main(void)
{
	t_cmd	cmd0;
	t_cmd	cmd1;
	t_cmd	cmd2;
	t_cmd	cmd3;

	cmd0.next = NULL;

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

	cmd0.argv = (char **)malloc(6 * sizeof(char*));
	cmd0.argv[0] = "echo";
	cmd0.argv[1] = "My";
	cmd0.argv[2] = "name";
	cmd0.argv[3] = "is";
	cmd0.argv[4] = "Greg!";
	cmd0.argv[5] = NULL;
	cmd0.fd_out = 1;
	cmd0.fd_in = 0;

	executor(&cmd0);

	return (0);
}