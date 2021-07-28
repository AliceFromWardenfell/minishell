#include "minishell.h"

static int	argc_is_1(t_data *d)
{
	char	*env_val;
	char	*tmp;

	if (get_env_val(d, "HOME=", &env_val))
		return (builtin_error("cd", NULL, NULL));
	if (get_env_val(d, "PWD=", &tmp))
		return (builtin_error("cd", env_val, NULL));
	if (env_val)
		if (chdir(env_val))
			return (builtin_error("cd", env_val, tmp));
	if (env_val && tmp)
		if (change_env_val(d, "OLDPWD=", tmp))
			return (builtin_error("cd", env_val, tmp));
	if (env_val && tmp)
		if (change_env_val(d, "PWD=", env_val))
			return (builtin_error("cd", env_val, tmp));
	free(env_val);
	free(tmp);
	return (0);
}

static int	cd_in_oldpwd(t_data *d)
{
	char	*tmp_pwd;
	char	*tmp_oldpwd;

	if (get_env_val(d, "PWD=", &tmp_pwd))
		return (builtin_error("cd", NULL, NULL));
	if (get_env_val(d, "OLDPWD=", &tmp_oldpwd))
		return (builtin_error("cd", tmp_pwd, NULL));
	if (chdir(tmp_oldpwd))
		return (builtin_error("cd", tmp_pwd, tmp_oldpwd));
	if (tmp_oldpwd && tmp_pwd)
		if (change_env_val(d, "OLDPWD=", tmp_pwd))
			return (builtin_error("cd", tmp_pwd, tmp_oldpwd));
	if (tmp_oldpwd && tmp_pwd)
		if (change_env_val(d, "PWD=", tmp_oldpwd))
			return (builtin_error("cd", tmp_pwd, tmp_oldpwd));
	free(tmp_pwd);
	free(tmp_oldpwd);
	return (0);
}

static int	cd_in_path(t_cmd *cmd, t_data *d)
{
	char	*old_pwd;
	char	*curr_dir;

	if (get_env_val(d, "PWD=", &old_pwd))
		return (builtin_error("cd", NULL, NULL));
	if (chdir(cmd->argv[1]))
		return (builtin_error("cd", old_pwd, NULL));
	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
		return (builtin_error("cd", old_pwd, NULL));
	if (old_pwd)
		if (change_env_val(d, "PWD=", curr_dir))
			return (builtin_error("cd", old_pwd, curr_dir));
	if (old_pwd)
		if (change_env_val(d, "OLDPWD=", old_pwd))
			return (builtin_error("cd", old_pwd, curr_dir));
	free(old_pwd);
	free(curr_dir);
	return (0);
}

static int	argc_is_2(t_cmd *cmd, t_data *d)
{
	if (!ft_strcmp(cmd->argv[1], "-"))
		if (cd_in_oldpwd(d))
			return (1);
	if (ft_strcmp(cmd->argv[1], "-"))
		if (cd_in_path(cmd, d))
			return (1);
	return (0);
}

int	cd_b(t_cmd *cmd, t_data *d)
{
	int	argc;

	argc = 0;
	while (cmd->argv[argc])
		argc++;
	if (argc > 2)
		printf("minishell: cd: too much arguments\n");
	if (argc == 1)
		if (argc_is_1(d))
			return (1);
	if (argc == 2)
		if (argc_is_2(cmd, d))
			return (1);
	return (0);
}
