#include "minishell.h"
#include <string.h>
#include <errno.h>

char	*get_temp_path(void)
{
	static int	i;
	char		*res;
	char		*temp;

	i++;
	temp = ft_itoa(i);
	res = ft_strjoin(TEMP_PATH, temp);
	free(temp);
	return (res);
}

int	print_free_return(char	*path, int to_return)
{
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	free(path);
	return (to_return);
}
