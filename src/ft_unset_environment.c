/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_environment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 15:15:34 by geliz             #+#    #+#             */
/*   Updated: 2020/03/01 17:58:32 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_env_and_set_next(t_data *in, t_env *temp, t_env *prev)
{
	ft_strdel(&temp->name);
	ft_strdel(&temp->value);
	if (!prev)
	{
		in->env = temp->next;
		temp->next = NULL;
	}
	else
	{
		prev->next = temp->next;
		temp->next = NULL;
	}
	free(temp);
}

int		ft_unset_environment(t_data *in)
{
	t_env	*temp;
	t_env	*prev;
	char	**args;

	temp = in->env;
	prev = NULL;
	if (in->arg == NULL)
		return (1);
	if (!(args = ft_strsplit(in->arg, ' ')))
		return (ft_malloc_error());
	while (temp)
	{
		if (ft_strcmp(temp->name, args[0]) == 0)
		{
			ft_delete_env_and_set_next(in, temp, prev);
			ft_delete_two_dimens_arr(&args);
			return (1);
		}
		prev = temp;
		temp = temp->next;
	}
	ft_delete_two_dimens_arr(&args);
	return (1);
}
