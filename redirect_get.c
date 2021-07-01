#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>

static int	get_heredocument(char *delimiter)
{
	int	fd;
	char *str;

	fd = open(TEMP_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (!fd)
		return (-1);
	str = readline("> ");
	while (str && ft_strncmp(str, delimiter, ft_strlen(str)))
	{	
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	free(str);
	close(fd);
	fd = open(TEMP_PATH, O_RDONLY);
	unlink(TEMP_PATH);
	return (fd);
}

static int	redir_output(int redir, char *path)
{
	int fd;
	
	if (redir == 1)
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir == 2)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

static int	redir_input(int redir, char *path)
{
	int fd;
	
	if (redir == 3)
		fd = open(path, O_RDONLY);
	else if (redir == 4)
		fd = get_heredocument(path);
	return (fd);
}

int	free_return_int(void *to_free, int to_return)
{
	free(to_free);
	return(to_return);
}

int	redirect_get(t_pipe *no_p, int redir, char *path)
{
	int	fd;

	if (redir == 1 || redir == 2)
	{	
		if (no_p->fd_out != 1)
			close(no_p->fd_out);
		fd = redir_output(redir, path);
		if (fd < 0)
			return (free_return_int(path, 0));
		no_p->fd_out = fd;
	}
	else if (redir == 3 || redir == 4)
	{	
		if (no_p->fd_in != 0)
			close(no_p->fd_in);
		fd = redir_input(redir, path);
		if (fd < 0)
			return (free_return_int(path, 0));
		no_p->fd_in = fd;
	}
	return (free_return_int(path, 1));
}
