/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_dir_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:13:44 by geliz             #+#    #+#             */
/*   Updated: 2020/02/24 17:11:02 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_cd_error(char *path)
{
	(void)path;
	ft_printf("errorweuweuweuew\n");
}

int		ft_change_dir_from_cur_dir(char *arg, char **env)
{
	int		res;
	char	*path;
	char	*pwd;
	int		i;

	i = 0;
	while (!(ft_strnstr(env[i], "PWD=", 4)))
		i++;
	if (!(pwd = ft_strsub(env[i], 4, (ft_strlen(env[i]) - 4))))
		return (-1);
	if (!(path = ft_strjoin_arg("%f %s %f", pwd, "/", arg)))
		return (-1);
	res = chdir(path);
	if (res != 0)
		ft_print_cd_error(path);
	ft_strdel(&path);
	return (1);
}

int		ft_change_dir_from_root(char *arg)
{
	int		res;

	res = chdir(arg);
	if (res != 0)
		ft_print_cd_error(arg);
	ft_strdel(&arg);
	return (1);
}

int		ft_change_dir_to_old_pwd(char **env)
{
	ft_printf("i'm here\n");
	(void)env;
	return (1);
}

int		ft_change_to_home_directory(char **env)
{
	int		i;
	char	*path;
	int		res;

	i = 0;
	while (!(ft_strnstr(env[i], "HOME=", 5)))
		i++;
	if (!(path = ft_strsub(&env[i][5], 0, (ft_strlen(env[i]) - 5))))
		return (-1);
	res = chdir(path);
	if (res != 0)
		ft_print_cd_error(path);
	ft_strdel(&path);
	return (1);
}

int		ft_get_first_arg(char *str, char **arg)
{
	int		i;
	char	*ret;

	if (!str)
		return (1);
	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	if (!(ret = ft_strsub(str, 0, i)))
		return (-1);
	*arg = ret;
	ft_printf("%s\n", ret);

	return (1);
}

int		ft_change_directory_cmd(t_data *in, char **env)
{
	char	*arg;
	int		ret;

	arg = NULL;
	if (ft_get_first_arg(in->arg, &arg) == -1)
		return (-1);
	if (arg == NULL || ft_strcmp(arg, "~") == 0 || ft_strcmp(arg, "--") == 0)
		ret = ft_change_to_home_directory(env);
	else if (ft_strcmp(arg, "-") == 0)
		ret = ft_change_dir_to_old_pwd(env);
	else if (arg[0] == '/')
		ret = ft_change_dir_from_root(arg);
	else
		ret = ft_change_dir_from_cur_dir(arg, env);
//	ft_change_old_pwd_in_env(env);
	return (1);
}
