#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

typedef struct		s_cmd
{
	char**			argv;
	int				fd_out;
	int				fd_in;
    struct s_cmd*	next;
}					t_cmd;

typedef struct		s_backup
{
	int				fd_out;
	int				fd_in;
}					t_backup;

t_backup			g_backup;

int		executor(t_cmd *cmd);
int		global_error(void);

#endif
