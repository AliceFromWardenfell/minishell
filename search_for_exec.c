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

int		has_slash(char *str) // make static
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == '/')
			return (1);
	return (0);
}

char	*search_for_exec(t_data *d, char *program_name)
{
	char			*val;
	char			**path;
	int				i;
	DIR				*dir;
	struct dirent	*ent;
	
	printf("program_name == %s\n", program_name); //remove

	if (get_env_val(d, "PATH=", &val))
		return (NULL);
	path = ft_split(val, ':'); //dont forget to free
	free(val);
	if (!path)
		return (NULL);
	
	//print_2d(path); // check
	
	i = -1;
	while (path[++i])
	{
		dir = opendir(path[i]);
		if (!dir)
			return (NULL);
		while ((ent = readdir(dir)) != NULL)
		{
			if (!ft_strcmp(ent->d_name, program_name))
			{
				val = custom_strjoin(path[i], program_name);
				clean_2d_arr(path);
				if (!val)
					return (NULL);
				printf("result will be: \"%s\"\n", val);
				return (val);
			}
		}
	}
	clean_2d_arr(path);
	return(program_name);
} // printf("%d. dir:\"%s\": %s\n", i, path[i], ent->d_name);
