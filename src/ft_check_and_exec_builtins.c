/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_and_exec_builtins.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 18:05:47 by geliz             #+#    #+#             */
/*   Updated: 2020/02/24 13:47:08 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_cd_cmd(t_data *in, char **env)
{
	int		res;

	if (ft_strcmp("cd", in->cmd) == 0)
	{
		res = ft_change_directory_cmd(in, env);
		return (res);
	}
	return (0);
}

int		ft_check_echo_cmd(t_data *in)
{
	if (ft_strcmp("echo", in->cmd) == 0)
	{
		ft_printf("%s\n", in->arg);
		return (1);
	}
	return (0);
}

int		ft_check_and_exec_builtins(t_data *in, char **env)
{
	int		ret;

	ret = ft_check_echo_cmd(in);
	ret = ft_check_cd_cmd(in, env);
	
	/*ret = 0;
	if (ft_check_echo_cmd(in) == 1)
		ret = 1;
	else if (ft_check_pwd_cmd(in) == 1)
		ret = 1;
	else if (ft_check_cd_cmd(in, env) == 1)
		ret = 1;*/
	return (ret);
}
