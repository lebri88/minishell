/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_command_in_way_or_cur_dir.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 21:52:32 by geliz             #+#    #+#             */
/*   Updated: 2020/03/06 13:59:12 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_stat(char *cname)
{
	struct stat		buff;
	struct stat		buff_s;

	lstat(cname, &buff);
	if (!(S_ISLNK(buff.st_mode)) && !(S_ISREG(buff.st_mode)))
		return (-2);
	if (!(S_ISLNK(buff.st_mode)))
		stat(cname, &buff_s);
	if ((buff.st_mode & S_IXUSR) || (buff.st_mode & S_IXGRP) ||
			(buff.st_mode & S_IXOTH))
		return (0);
	return (-2);
}

int		ft_get_path_and_name(t_data *in, char **name, char **path)
{
	int		i;
	int		slpos;
	char	*str;

	i = 0;
	slpos = 0;
	str = in->cmd;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
			slpos = i;
		i++;
	}
	if (slpos == 0)
		return (-1);
	if (!(*name = ft_strdup(&str[slpos + 1])))
		return (-1);
	if (!(*path = ft_strsub(str, 0, (slpos + 1))))
		return (-1);
	if (ft_strnstr(*path, "./", 2))
	{
		if (!(*path = ft_strjoin_arg("%s %s %f", in->curdir, "/", *path)))
			return (-1);
	}
	return (1);
}

int		ft_close_dir_and_free_str(DIR *dir, char *fname, char *fpath)
{
	closedir(dir);
	ft_strdel(&fname);
	ft_strdel(&fpath);
	return (0);
}

int		ft_find_command_in_way_or_cur_dir(t_data *in, char **cname)
{
	DIR				*dir;
	char			*fname;
	char			*fpath;
	struct dirent	*dr;

	if (ft_strcmp(in->cmd, "/") == 0)
	{
		if (!(*cname = ft_strdup("/")))
			return (0);
	}
	if (ft_get_path_and_name(in, &fname, &fpath) == -1)
		return (-1);
	if (!(dir = opendir(fpath)))
		return (-1);
	while ((dr = readdir(dir)) != NULL)
	{
		if (ft_strcmp(dr->d_name, fname) == 0)
		{
			if (!(*cname = ft_strdup(in->cmd)))
				return (-1);
			return (ft_close_dir_and_free_str(dir, fname, fpath));
		}
	}
	ft_close_dir_and_free_str(dir, fname, fpath);
	return (-1);
}
