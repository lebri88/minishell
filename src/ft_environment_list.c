/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:29:38 by geliz             #+#    #+#             */
/*   Updated: 2020/03/01 16:06:09 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_take_env_from_struct(t_data *in)
{
	t_env	*temp;
	int		i;
	char	**ret;

	i = 0;
	temp = in->env;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	if (!(ret = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	ret[i] = NULL;
	i = 0;
	temp = in->env;
	while (temp)
	{
		if (!(ret[i] = ft_strjoin_arg("%s%s%s", temp->name, "=", temp->value)))
			return (NULL);
		temp = temp->next;
		i++;
	}
	return (ret);
}

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

t_env	*ft_create_next_t_env_list(char *env, t_env *prev)
{
	t_env	*list;
	int		i;

	(void)prev;
	if (!(list = malloc(sizeof(t_env))))
		return (NULL);
	i = 0;
	while (env[i] != '=')
		i++;
	if (!(list->name = ft_strsub(env, 0, i)))
		return (NULL);
	if (!(list->value = ft_strdup(&env[i + 1])))
		return (NULL);
	list->next = NULL;
	if (prev)
		prev->next = list;
	return (list);
}

t_env	*ft_env_to_list(char **env)
{
	t_env	*first;
	t_env	*prev;
	t_env	*cur;

	first = NULL;
	prev = NULL;
	while (*env)
	{
		if (!(cur = ft_create_next_t_env_list(*env, prev)))
			return (NULL);
		if (!first)
			first = cur;
		prev = cur;
		env++;
	}
	return (first);
}
