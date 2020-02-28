/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_dir_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:13:44 by geliz             #+#    #+#             */
/*   Updated: 2020/02/28 18:47:48 by geliz            ###   ########.fr       */
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
		ret = ft_change_dir_from_root(in, arg);
	else
		ret = ft_change_dir_from_cur_dir(arg, in);
	ft_strdel(&arg);	
	if (ret == -1)
		return (ret);
	if (ret == 1)
	{
		if (ft_change_old_pwd_in_env(in) == -1)
			return (-1);
	}
	return (1);
}
