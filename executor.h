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

# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7

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
int		is_builtin(t_cmd *cmd);
int		do_builtin(t_cmd *cmd, int builtin);
int		echo_b(t_cmd *cmd);

#endif
