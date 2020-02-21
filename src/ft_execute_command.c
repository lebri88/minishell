/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 17:02:21 by geliz             #+#    #+#             */
/*   Updated: 2020/02/21 18:53:22 by geliz            ###   ########.fr       */
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
		if (ft_find_command_in_opened_dir(pd, in) == 1)
			return (i);
		i++;
	}
	return (i);
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

int		ft_execute_command(t_data *in, char **env, int i)
{
	char	*cname;
	char	**args;
	int		err;
	pid_t	c_pid;

	cname = ft_strjoin_arg("%s %s %s", in->env_path[i], "/", in->cmd);
	if ((err = access(cname, X_OK)) == -1)
	{
		ft_printf("ACCESS ERROR HERE %s\n", cname);
		return (-1); //ft_print_error()
	}
	args = ft_create_args_list(in);
	c_pid = fork();
	if (c_pid == 0)
	{
		if ((execve(cname, args, env)) == -1)
			return (-1);
		
	}
	else if (c_pid > 0)
	{
		
		//delete_args;
		return (0);
	}
	return (0);
}

int		ft_execute_command_hub(t_data *in, char **env)
{
	/*
	int		i;
	
	ft_printf("cmd = %s\narg = %s\npath = %s\n", in->cmd, in->arg, in->path);
	i = 0;
	(void)env;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	while (in->env_path[i] != NULL)
	{
		ft_printf("%s\n", in->env_path[i]);
		i++;
	}
	if (in->path)
		return (1);
	*/
	int		i;

	i = ft_find_command_in_path_dirs(in);
	ft_printf("i = %i, dir = %s", i, in->env_path[i]);
	ft_execute_command(in, env, i);
	(void)env;
	return (0);
}
