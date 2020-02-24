/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:29:38 by geliz             #+#    #+#             */
/*   Updated: 2020/02/24 19:16:22 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove_env_list(t_env *list)
{
	t_env	*temp;

	while (list)
	{
		ft_strdel(&list->name);
		ft_strdel(&list->value);
		temp = list->next;
		list->next = NULL;
		free(list);
		list = temp;
	}
}

t_env	*ft_env_to_list(char **env)
{
	int		i;
	int		j;
	t_env	*ret;
	t_env	*temp;

	i = 0;
	j = 0;
	temp = NULL;
	while (env[i])
	{
		if (!(ret = malloc(sizeof(t_env))))
			return (NULL);
		while (env[i][j] != '=')
			j++;
		ret->name = ft_strsub(env[i], 0, j);
		ret->value = ft_strdup(&env[i][j + 1]);
		ret->next = temp;
		if (!ret->name || !ret->value)
			return (NULL);
		temp = ret;
		j = 0;
		i++;
	}
	return (ret);
}
