#include "minishell.h"

static char	*custom_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
	{
		res[i] = *(s1++);
		i++;
	}
	res[i] = '/';
	i++;
	while (*s2 != '\0')
	{
		res[i] = *(s2++);
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	has_slash(char *str) // make static
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == '/')
			return (1);
	return (0);
}

char	*search_for_exec(t_data *d, char *program_name, int	*was_allocation)
{
	char			*val;
	char			**path;
	int				i;
	DIR				*dir;
	struct dirent	*ent;
	// int				cmd_exists;

	if (get_env_val(d, "PATH=", &val))
		return (NULL);
	if (!val)
	{
		val = ft_strjoin("./", program_name);
		if (!val)
			return (NULL);
		*was_allocation = 1;
		return(val);
	}
	path = ft_split(val, ':'); //dont forget to free // leak when ./minishell; abracadabra
	if (val)
		free(val); // if was added; not sure about it
	if (!path)
		return (NULL);
	i = -1;
	// cmd_exists = 0;
	while (path[++i])
	{
		dir = opendir(path[i]);
		if (!dir && errno != EACCES && errno != ENOENT && errno != ENOTDIR)
		{
			clean_2d_arr(path);
			return (NULL);
		}
		else if (dir)
		{
			// cmd_exists = 1;
			while ((ent = readdir(dir)) != NULL) // readdir ret NULL // distinguish error from end
			{
				if (!ft_strcmp(ent->d_name, program_name))
				{
					val = custom_strjoin(path[i], program_name);
					clean_2d_arr(path);
					closedir(dir);
					if (!val)
						return (NULL);
					*was_allocation = 1;
					return (val);
				}
			}
			if (closedir(dir) < 0)
			{
				clean_2d_arr(path);
				return (NULL);
			}
		}
	}
	clean_2d_arr(path);
	// if (!cmd_exists)
	// 	return (NULL);
	return (program_name);
} // printf("%d. dir:\"%s\": %s\n", i, path[i], ent->d_name);
