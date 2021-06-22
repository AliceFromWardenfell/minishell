#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct		s_cmd
{
	char**			argv;
	int				fd_out;
	int				fd_in;
    struct s_cmd*	next;
}					t_cmd;

#endif
