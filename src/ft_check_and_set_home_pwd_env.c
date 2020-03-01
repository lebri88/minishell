/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_and_set_home_pwd_env.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 14:37:42 by geliz             #+#    #+#             */
/*   Updated: 2020/03/01 15:05:32 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_add_pwd_to_env(t_data *in, t_env *last)
{
	char	*temp;

	if (!(temp = ft_strjoin_arg("%s %f", "PWD=", ft_get_current_dir())))
		return (-1);
	if (!last)
	{
		if (!(in->env = ft_create_next_t_env_list(temp, NULL)))
			return (-1);
	}
	else
	{
		if (!(ft_create_next_t_env_list(temp, last)))
			return (-1);
	}
	return (1);
}

t_env	*ft_check_in_env(t_data *in, char *str)
{
	t_env	*temp;
	t_env	*last;

	temp = in->env;
	while (temp)
	{
		if (ft_strcmp(temp->name, str) == 0)
		{
			str = NULL;
			return (NULL);
		}
		last = temp;
		temp = temp->next;
	}
	str = NULL;
	return (last);
}

int		ft_check_and_set_home_pwd_env(t_data *in)
{
	t_env	*last;

	last = NULL;
	if (!in->env)
	{
		if (ft_add_pwd_to_env(in, NULL) == -1)
			return (-1);
	}
	else
		last = ft_check_in_env(in, "PWD");
	if (last)
	{
		if (ft_add_pwd_to_env(in, last) == -1)
			return (-1);
	}
	last = ft_check_in_env(in, "HOME");
	if (last)
	{
		if (!ft_create_next_t_env_list("HOME=/", last))
			return (-1);
	}
	return (1);
}
