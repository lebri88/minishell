/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_and_exec_builtins.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 18:05:47 by geliz             #+#    #+#             */
/*   Updated: 2020/03/01 19:01:47 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_print_arg_echo(char *str)
{
	int		i;
	char	*s;
	char	*c;

	i = 0;
	s = NULL;
	if (!str)
	{
		ft_printf("\n");
		return (1);
	}
	while (str[i] != '\0')
	{
		while (str[i] == '"')
			i++;
		if (str[i] != '\0')
		{
			c = ft_strsub(&str[i], 0, 1);
			s = ft_strjoin_arg("%f %f", s, c);
			i++;
		}
	}
	ft_printf("%s\n", s);
	ft_strdel(&s);
	return (1);
}

int		ft_check_env_group_cmd(t_data *in)
{
	if (ft_strcmp(in->cmd, "env") == 0 || ft_strcmp(in->cmd, "ENV") == 0)
		return (ft_print_all_of_env_values(in));
	if (ft_strcmp(in->cmd, "setenv") == 0)
		return (ft_set_environment(in));
	if (ft_strcmp(in->cmd, "unsetenv") == 0)
		return (ft_unset_environment(in));
	return (0);
}

int		ft_check_cd_cmd(t_data *in)
{
	int		res;

	if (ft_strcmp("cd", in->cmd) == 0 || ft_strcmp("CD", in->cmd) == 0)
	{
		res = ft_change_directory_cmd(in);
		return (1);
	}
	return (0);
}

int		ft_check_echo_cmd(t_data *in)
{
	if (ft_strcmp("echo", in->cmd) == 0)
	{
		if (ft_print_arg_echo(in->arg) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int		ft_check_and_exec_builtins(t_data *in)
{
	int		ret;

	ret = ft_check_cd_cmd(in);
	if (ret == 0)
		ret = ft_check_env_group_cmd(in);
	if (ret == 0)
		ret = ft_check_echo_cmd(in);
	return (ret);
}
