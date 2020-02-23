/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 17:02:21 by geliz             #+#    #+#             */
/*   Updated: 2020/02/23 21:46:02 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_find_command_in_opened_dir(DIR *pd, t_data *in)
{
	struct dirent	*entry;

	while ((entry = readdir(pd)) != NULL)
	{
		if (ft_strcmp(entry->d_name, in->cmd) == 0)
		{
			closedir(pd);
			return (1);
		}
	}
	closedir(pd);
	return (0);
}

int		ft_find_command_in_path_dirs(t_data *in)
{
	int		i;
	DIR		*pd;

	i = 0;
	while (in->env_path[i] != NULL)
	{
		pd = opendir(in->env_path[i]);
		if (pd && ft_find_command_in_opened_dir(pd, in) == 1)
			return (i);
		i++;
	}
	return (-1);
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

int		ft_execute_command(t_data *in, char **env, char *cname)
{
	char	**args;
	pid_t	c_pid;
	int		status;

	args = ft_create_args_list(in);
	c_pid = fork();
	if (c_pid == 0)
	{
		if ((execve(cname, args, env)) == -1)
			return (-1);
	}
	else if (c_pid > 0)
	{
		waitpid(c_pid, &status, 0);
		ft_delete_two_dimens_arr(&args);
		return (0);
	}
	return (0);
}

int		ft_execute_command_hub(t_data *in, char **env)
{
	int		i;
	char	*cname;
	int		err;

	err = 0;
	cname = NULL;
	if (ft_check_and_exec_builtins(in, env) == 1)
		return (0);
	i = ft_find_command_in_path_dirs(in);
	if (i == -1)
		err = -1;
	if (err == 0)
		cname = ft_strjoin_arg("%s %s %s", in->env_path[i], "/", in->cmd);
	if (err == 0 && access(cname, X_OK) == -1)
		err = -2;
//	ft_printf("i = %i, dir = %s", i, in->env_path[i]);
	if (err == 0)
		ft_execute_command(in, env, cname);
	ft_strdel(&cname);
	ft_print_error(err, in);
	return (0);
}
