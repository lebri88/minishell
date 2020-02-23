/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_directory_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 21:48:20 by geliz             #+#    #+#             */
/*   Updated: 2020/02/23 22:23:48 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_first_arg(t_data *in, char **env)
{
	char	**ret;
	char	*arg;
	int		i;

	i = 0;
	if (in->arg)
	{
		while (in->arg[i] != ' ' && in->arg[i] != '\0')
			i++;
		arg = ft_strsub(in->arg, 0, i);
		ret = ft_strsplit(arg, '/');
		ft_strdel(&arg);
	}
	else
	{
		while (!(ft_strnstr(env[i], "HOME=", 5)))
			i++;
		ret = ft_strsplit(&env[i][5], '/');
	}
	return (ret);
}

void	ft_change_directory_cmd(t_data *in, char **env)
{
	char	**arg;
	char	**curdir;
	int		i_arg;
	int		i_cdir;

	arg = ft_get_first_arg(in, env);
	curdir = ft_strsplit(in->curdir, '/');
	i_arg = 0;
	i_cdir = 0;
	while (curdir[i_cdir])
		i_cdir++;
	i_cdir--;
	while (arg[i_arg])
	{
		if (ft_strcmp(arg[i_arg], ".") == 0)
			continue;
		else if (ft_strcmp(arg[i_arg], ".."))
			
		
		i_arg++;
	}
	while (*arg)
	{
		ft_printf("%s\n", *arg);
		arg++;
	}
	(void)env;
}
