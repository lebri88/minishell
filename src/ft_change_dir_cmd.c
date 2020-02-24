/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_dir_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:13:44 by geliz             #+#    #+#             */
/*   Updated: 2020/02/24 19:24:16 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_change_old_pwd_in_env(t_data *in)
{
	t_env	*temp;

	temp = in->env;
	while (ft_strcmp(temp->name, "OLDPWD") != 0)
		temp = temp->next;
	if (temp)
	{
		ft_strdel(&temp->value);
		if (!(temp->value = ft_strdup(in->curdir)))
			return (-1);
	}
	temp = in->env;
	while (ft_strcmp(temp->name, "PWD") != 0)
		temp = temp->next;
	if (temp)
	{
		ft_strdel(&temp->value);
		temp->value = ft_get_current_dir();
		ft_strdel(&in->curdir);
		if (!(in->curdir = ft_strdup(temp->value)))
			return (-1);
	}
	return (1);
}

void	ft_print_cd_error(char *path)
{
	ft_fprintf(2, "MSHELL$>: cd: %s: No such file or directory\n", path);
}

int		ft_change_dir_from_cur_dir(char *arg, t_data *in)
{
	int		res;
	char	*path;
	t_env	*temp;

	temp = in->env;
	while (ft_strcmp(temp->name, "PWD") != 0)
		temp = temp->next;
	if (!(path = ft_strjoin_arg("%s %s %f", temp->value, "/", arg)))
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

int		ft_change_dir_to_old_pwd(t_data *in)
{
	t_env	*temp;
	int		res;

	res = 0;
	temp = in->env;
	while (ft_strcmp(temp->name, "OLDPWD") != 0)
		temp = temp->next;
	if (temp)
		res = chdir(temp->value);
	if (res != 0)
	{
		ft_print_cd_error(temp->value);
		return (0);
	}
	return (1);
}

int		ft_change_to_home_directory(t_data *in)
{
	char	*path;
	int		res;
	t_env	*env;

	env = in->env;
	while ((ft_strcmp(env->name, "HOME")) != 0)
		env = env->next;
	path = env->value;
	res = chdir(path);
	if (res != 0)
	{
		ft_print_cd_error(path);
		return (0);
	}
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
	return (1);
}

int		ft_change_directory_cmd(t_data *in)
{
	char	*arg;
	int		ret;

	arg = NULL;
	if (ft_get_first_arg(in->arg, &arg) == -1)
		return (-1);
	if (arg == NULL || ft_strcmp(arg, "~") == 0 || ft_strcmp(arg, "--") == 0)
		ret = ft_change_to_home_directory(in);
	else if (ft_strcmp(arg, "-") == 0)
		ret = ft_change_dir_to_old_pwd(in);
	else if (arg[0] == '/')
		ret = ft_change_dir_from_root(arg);
	else
		ret = ft_change_dir_from_cur_dir(arg, in);
	if (ret == -1)
		return (ret);
	ft_printf("ret = %i\n", ret);
	if (ret == 1)
	{
		if (ft_change_old_pwd_in_env(in) == -1)
		{
			ft_printf("ERRRORORROR!!!!\n");
			return (-1);
		}
		t_env	*tmp;
		tmp = in->env;
		while (ft_strcmp(tmp->name, "OLDPWD") != 0)
			tmp = tmp->next;
		ft_printf("OLDPWD = %s\n", tmp->value);
		tmp = in->env;
		while (ft_strcmp(tmp->name, "PWD") != 0)
			tmp = tmp->next;
		ft_printf("PWD = %s\n", tmp->value);
	}
	return (1);
}
