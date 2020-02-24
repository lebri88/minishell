/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_directory_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 21:48:20 by geliz             #+#    #+#             */
/*   Updated: 2020/02/24 17:11:07 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_get_first_arg(t_data *in, char **env, char ***arr)
{
	char	*arg;
	int		i;
	int		fromroot;

	i = 0;
	fromroot = 0;
	if (in->arg)
	{
		while (in->arg[i] != ' ' && in->arg[i] != '\0')
			i++;
		arg = ft_strsub(in->arg, 0, i);
		if (arg[0] == '/')
			fromroot = 1;
		*arr = ft_strsplit(arg, '/');
		ft_strdel(&arg);
	}
	else
	{
		while (!(ft_strnstr(env[i], "HOME=", 5)))
			i++;
		if (env[i][5] == '/')
			fromroot = 1;
		*arr = ft_strsplit(&env[i][5], '/');
	}
	return (fromroot);
}

int		ft_check_cd_from_root_res(int res, t_data *in, char *path)
{
	if (res != 0)
	{
		chdir(in->curdir);
		ft_fprintf(2, "MSHELL: cd: %s: No such file or directory\n", path);
		ft_strdel(&path);
	}
	else
	{
		ft_strdel(&in->curdir);
		if (!(in->curdir = ft_strdup(path)))
			return (-1);
		ft_strdel(&path);
	}
	return (1);
}
/*
char	*ft_return_to_previous_path(char *path, char *arg)
{
	int		i;
	char	*ret;
	
	if (ft_strcmp(arg, ".") == 0)
		return (path);
	if (ft_strcmp(path, "/") == 0)
		return (path);
	i = 0;
	i = ft_strlen(path);
	i
	while (path[i] != '/')
		i--;
	ret = ft_strsub
}
*/
int		ft_cd_from_root(t_data *in, char **arg)
{
	char	*path;
	int		res;
	int		i;

	if (!(path = ft_strdup("/")))
		return (-1);
	i = 0;
	res = chdir(path);
	while (arg[i])
	{
		if (!(path = ft_strjoin_arg("%f %s %s", path, arg[i], "/")))
			return (-1);
		if (res == 0)
			res = chdir(path);
		i++;
	}
	res = ft_check_cd_from_root_res(res, in, path);
	return (res);
}

int		ft_cd_from_current_dir(t_data *in, char **env, char **arg, char **cdir)
{
	(void)in;
	(void)env;
	(void)arg;
	(void)cdir;
	return (1);
}

int		ft_change_directory_cmd(t_data *in, char **env)
{
	char	**arg;
	int		fromroot;
	int		ret;

	if (ft_get_first_arg(in, env, &arg) == -1)
		return (-1);
//	ret = 1;
//	fromroot = ft_get_first_arg(in, env, &arg);
//	if (fromroot == 1 && ft_cd_from_root(in, arg) == -1)
//		ret = -1;
//	if (fromroot == 0)
//	{
//		if (ft_cd_from_current_dir(in, env, arg, cdir) == -1)
//			ret = -1;
//	}
	ft_delete_two_dimens_arr(&arg);
/*	while (cdir[i])
		i++;
	i--;*/
	
/*	while (*arg)
	{
		ft_printf("%s\n", *arg);
		arg++;
	}*/
	return (ret);
}
