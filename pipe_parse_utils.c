#include "minishell.h"

void	tpipe_init(t_pipe *no_p, int count)
{
	no_p->fd_in = 0;
	no_p->fd_out = 1;
	no_p->no_quote = (t_char *)malloc(sizeof(t_char) * (count + 1));
}
