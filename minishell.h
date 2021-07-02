#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"

# define TEMP_PATH "/home/vyrm/exercises/minishell/temp"

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
	struct s_cmd	*next;
}	t_cmd;

int quote_check(char *str);
t_char	*unquote(char *str);
int ft_is_blank(t_char *c);
int	pipe_check(t_char *no_quote);
void	*pipe_clear(t_pipe *no_pipe);
void	ft_charcpy(t_char *to, char c, int escaped);
void	tpipe_init(t_pipe *no_p, int count);
t_pipe	*piper(t_char *no_q);
int	redirect_sycheck(t_pipe *no_pipe);
t_char	*check_env(t_char *no_q, char **env);
int is_key(char c);
int	key_length(t_char *no_q);
void *free_return_null(void *to_free);
int	tchar_strlen(t_char *str);
t_char	*tchardup(t_char *str);
int	key_check(t_char *no_q);
int	free_return_int(void *to_free, int to_return);
int	print_free_return(int fd, char	*path, int to_return);
int	redirect_get(t_pipe *no_p, int redir, char *path);
char	*get_temp_path(void);
int	redirection_parse(t_pipe *no_p, char **env);
int	get_word_size(t_char *no_q);
char	*ch_transform(t_char *no_q);
t_char	*get_redir_path(t_char *no_quote, int i);
t_char	*get_new_noq(t_char *no_quote, int i);
t_char	*redir_env(t_char *no_q, char **env);
int	env_parse(t_pipe *no_p, char **env);
void	*array_clear(char **ar);
char	**lexer(t_char *no_q);
void	cmd_clear(t_cmd *start);
t_cmd *create_cmd(t_pipe *no_p);

#endif