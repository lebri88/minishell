/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_dir_variants.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:29:59 by geliz             #+#    #+#             */
/*   Updated: 2020/02/28 18:47:52 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_cd_error(char *path)
{
	ft_fprintf(2, "cd: %s: No such file or directory\n", path);
}

int		ft_change_dir_from_cur_dir(char *arg, t_data *in)
{
	int		res;
	char	*path;
	t_env	*temp;

	temp = in->env;
	while (ft_strcmp(temp->name, "PWD") != 0)
		temp = temp->next;
	if (!(path = ft_strjoin_arg("%s %s %s", temp->value, "/", arg)))
		return (-1);
	res = chdir(path);
	if (res != 0)
		ft_print_cd_error(arg);
	ft_strdel(&path);
	return (1);
}

int		ft_change_dir_from_root(t_data *in, char *arg)
{
	int		res;

	res = chdir(arg);
	if (res != 0)
	{
		ft_print_cd_error(arg);
		return (-1);
	}
	(void)in;
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
		return (-1);
	}
	return (1);
}

int		ft_change_to_home_directory(t_data *in)
{
	char	*path;
	int		res;
	t_env	*temp;

	temp = in->env;
	while ((ft_strcmp(temp->name, "HOME")) != 0)
		temp = temp->next;
	if (!(path = ft_strdup(temp->value)))
		return (-1);
	res = chdir(path);
	if (res != 0)
	{
		ft_print_cd_error(path);
		return (-1);
	}
	ft_strdel(&path);
	return (1);
}
