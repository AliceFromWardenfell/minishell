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

typedef struct s_cmd
{
	char			**argv;
	int				fd_out;
	int				fd_in;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_backup
{
	int				fd_out;
	int				fd_in;
}					t_backup;

typedef struct s_data
{
	struct s_backup	backup;
	char			**env;
	int				amount_of_alloc_lines; // has to be init on 0
}					t_data;

int		executor(t_cmd *cmd, const char **envp);
int		is_builtin(t_cmd *cmd);
int		do_builtin(t_cmd *cmd, t_data *d, int builtin);
int		echo_b(t_cmd *cmd);
int		cd_b(t_cmd *cmd, t_data *d);
int		pwd_b(void);
int		env_b(t_data *d);
int		export_b(t_cmd *cmd, t_data *d);
int		dup_envp(t_data *d, const char **envp);
int		change_env_val(t_data *d, char *key, char *val);
int		get_env_val(t_data *d, char *key, char **val);
int		global_error(t_data *d);
int		builtin_error(char *builtin, char *to_free1, char *to_free2);
void	clean(t_data *d);
void	print_2d(char **arr); // remove

#endif
