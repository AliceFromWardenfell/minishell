#include "minishell.h"

static char	*clean_return(char **path)
{
	clean_2d_arr(path);
	return (NULL);
}

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

static char	*path_loop_clean(t_data *d, DIR *dir, char **path, int i)
{
	char			*val;

	val = custom_strjoin(path[i], d->program_name);
	clean_2d_arr(path);
	closedir(dir);
	if (!val)
		return (NULL);
	d->was_allocation = 1;
	return (val);
}

static char	*path_loop(t_data *d, char **path, char *program_name, int i)
{
	DIR				*dir;
	struct dirent	*ent;

	d->program_name = program_name;
	while (path[++i])
	{
		dir = opendir(path[i]);
		if (!dir && errno != EACCES && errno != ENOENT && errno != ENOTDIR)
			return (clean_return(path));
		else if (dir)
		{
			ent = readdir(dir);
			while (ent != NULL)
			{
				if (!ft_strcmp(ent->d_name, program_name))
					return (path_loop_clean(d, dir, path, i));
				ent = readdir(dir);
			}
			if (closedir(dir) < 0)
				return (clean_return(path));
		}
	}
	clean_2d_arr(path);
	return (program_name);
}

char	*search_for_exec(t_data *d, char *program_name)
{
	char			*val;
	char			**path;

	if (get_env_val(d, "PATH=", &val))
		return (NULL);
	if (!val)
	{
		val = ft_strjoin("./", program_name);
		if (!val)
			return (NULL);
		d->was_allocation = 1;
		return (val);
	}
	path = ft_split(val, ':');
	if (val)
		free(val);
	if (!path)
		return (NULL);
	val = path_loop(d, path, program_name, -1);
	if (!val)
		return (NULL);
	return (val);
}
