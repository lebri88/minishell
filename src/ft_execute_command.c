/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 17:02:21 by geliz             #+#    #+#             */
/*   Updated: 2020/03/01 15:34:01 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_open_dir_and_find_command(char *openit, t_data *in)
{
	DIR				*pd;
	struct dirent	*entry;
	char			*ret;

	pd = opendir(openit);
	while (pd && ((entry = readdir(pd)) != NULL))
	{
		if (ft_strcmp(entry->d_name, in->cmd) == 0)
		{
			if (!(ret = ft_strdup(openit)))
				return (NULL);
			closedir(pd);
			return (ret);
		}
	}
	closedir(pd);
	return (NULL);
}

char	*ft_find_command_in_path_dirs(t_data *in)
{
	int		i;
	char	**path;
	t_env	*temp;
	char	*ret;

	i = 0;
	temp = in->env;
	while (temp && ft_strcmp(temp->name, "PATH") != 0)
		temp = temp->next;
	if (!temp)
		return (NULL);
	if (!(path = ft_strsplit(temp->value, ':')))
		return (NULL);
	while (path[i])
	{
		if ((ret = ft_open_dir_and_find_command(path[i], in)) != NULL)
		{
			ft_delete_two_dimens_arr(&path);
			return (ret);
		}
		i++;
	}
	ft_delete_two_dimens_arr(&path);
	return (NULL);
}

char	**ft_create_args_list(t_data *in)
{
	char	*temp;
	char	**ret;

	temp = ft_strjoin_arg("%s %s %s", in->cmd, " ", in->arg);
	ret = ft_strsplit(temp, ' ');
	ft_strdel(&temp);
	return (ret);
}

int		ft_execute_command(t_data *in, char *cname)
{
	char	**args;
	pid_t	c_pid;
	int		status;
	char	**env;

	args = ft_create_args_list(in);
	env = ft_take_env_from_struct(in);
	c_pid = fork();
	if (c_pid == 0)
	{
		if ((execve(cname, args, env)) == -1)
			return (-1);
	}
	else if (c_pid != 0)
	{
		waitpid(c_pid, &status, 0);
		ft_delete_two_dimens_arr(&args);
		ft_delete_two_dimens_arr(&env);
		return (0);
	}
	return (0);
}

int		ft_execute_command_hub(t_data *in)
{
	char	*cname;
	int		err;
	char	*path;

	err = 0;
	cname = NULL;
	if (ft_check_and_exec_builtins(in) == 1)
		return (0);
	path = ft_find_command_in_path_dirs(in);
	if (!path)
		err = -1;
	if (err == 0)
		cname = ft_strjoin_arg("%f %s %s", path, "/", in->cmd);
	if (err == -1)
		err = ft_find_command_in_way_or_cur_dir(in, &cname);
	if (err == 0 && access(cname, X_OK) == -1)
		err = -2;
	if (err == 0)
		ft_execute_command(in, cname);
	ft_strdel(&cname);
	ft_print_error(err, in);
	return (0);
}
