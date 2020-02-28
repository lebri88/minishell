/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_or_change_env_values.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 20:00:55 by geliz             #+#    #+#             */
/*   Updated: 2020/02/28 20:47:48 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_print_all_of_env_values(t_data *in)
{
	t_env	*temp;

	temp = in->env;
	while (temp)
	{
		ft_printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
	return (1);
}

int		ft_set_environment(t_data *in)
{
	char	**args;

	if (!(args = ft_strsplit(in->arg, ' ')))
		return (-1);
	return (0);
}
