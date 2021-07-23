#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
#include <sys/wait.h> // flags for waitpid()

# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7

# define TEMP_PATH "/Users/airon/goinfre/temp"

typedef struct s_char
{
	char	c;
	int		escaped;
}	t_char;

typedef struct s_pipe
{
	t_char	*no_quote;
	int		fd_in;
	int		fd_out;
}	t_pipe;

typedef struct s_cmd
{
	char			**argv;
	int				fd_in;
	int				fd_out;
	int				pid;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_backup
{
	int				fd_out;
	int				fd_in;
}					t_backup;

typedef struct s_data
{
	struct s_backup	backup;
	char			**env;
	int				amount_of_alloc_lines;
	int				status_code;
}					t_data;

t_cmd	*parser(char *str, char **env, t_data *d);
int		quote_check(char *str);
t_char	*unquote(char *str);
int		ft_is_blank(t_char *c);
int		pipe_check(t_char *no_quote);
void	*pipe_clear(t_pipe *no_pipe);
void	*pipe_clear_no_c(t_pipe *no_pipe);
void	ft_charcpy(t_char *to, char c, int escaped);
t_char	*tpipe_fill(t_char **no_q);
t_pipe	*piper(t_char *no_q);
int		redirect_sycheck(t_pipe *no_pipe);
t_char	*check_env(t_char *no_q, char **env, t_data *d);
int		is_key(char c);
int		key_length(t_char *no_q);
void	*free_return_null(void *to_free);
int		tchar_strlen(t_char *str);
t_char	*tchardup(t_char *str);
int		key_check(t_char *no_q);
char	*ft_exit_status(t_data *d);
int		free_return_int(void *to_free, int to_return);
int		print_free_return(char	*path, int to_return);
int		redirect_get(t_pipe *no_p, int redir, char *path);
char	*get_temp_path(void);
int		redirection_parse(t_pipe *no_p, char **env, t_data *d);
int		get_word_size(t_char *no_q);
char	*ch_transform(t_char *no_q);
t_char	*get_redir_path(t_char *no_quote, int i);
t_char	*get_new_noq(t_char *no_quote, int i);
t_char	*redir_env(t_char *no_q, char **env, int redir, t_data *d);
int		env_parse(t_pipe *no_p, char **env, t_data *d);
void	*array_clear(char **ar);
char	**lexer(t_char *no_q);
void	cmd_clear(t_cmd *start);
t_cmd	*create_cmd(t_pipe *no_p);
void	sig_handler(int sig);

int		executor(t_cmd *cmd, t_data *d);
int		has_slash(char *str); // make static
int		is_builtin(t_cmd *cmd);
void	do_builtin(t_cmd *cmd, t_data *d, int builtin);
int		echo_b(t_cmd *cmd);
int		cd_b(t_cmd *cmd, t_data *d);
int		pwd_b(void);
int		env_b(t_data *d);
int		export_b(t_cmd *cmd, t_data *d);
int		unset_b(t_cmd *cmd, t_data *d);
void	exit_b(t_cmd *cmd, t_data *d);
int		key_exist(t_data *d, char *key, int	*line_num);
int		dup_envp(t_data *d, const char **envp);
int		change_env_val(t_data *d, char *key, char *val);
int		get_env_val(t_data *d, char *key, char **val);
int		global_error(t_data *d);
int		builtin_error(char *builtin, char *to_free1, char *to_free2);
void	clean_2d_arr(char **arr);
void	clean(t_data *d);
void	init(t_data *d);
void	print_2d(char **arr); // remove
char	*search_for_exec(t_data *d, char *program_name, int *was_allocation);

#endif