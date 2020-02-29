/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_or_change_env_values.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 20:00:55 by geliz             #+#    #+#             */
/*   Updated: 2020/02/29 22:00:57 by geliz            ###   ########.fr       */
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

int		ft_add_env_to_list(t_data *in, char **args)
{
	char	*env_str;
	t_env	*temp;

	temp = in->env;
	if (ft_strchr(args[0], '='))
	{
		ft_fprintf(2, "setenv: NAME shouldn't contain an '=' character\n");
		return (1);
	}
	while (temp->next != NULL)
		temp = temp->next;
	if (!(env_str = ft_strjoin_arg("%s %s %s", args[0], "=", args[1])))
		return (-1);
	temp = ft_create_next_t_env_list(env_str, temp);
	ft_strdel(&env_str);
	return (1);
}

int		ft_change_existent_env(t_env *temp, char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		ft_fprintf(2, "setenv: Usage: setenv ");
		ft_fprintf(2, "char *NAME, char *VALUE, int OVERWRITE\n");
		return (1);
	}
	if (ft_atoi(args[2]) != 0)
	{
		ft_strdel(&temp->value);
		if (!(temp->value = ft_strdup(args[1])))
			return (-1);
	}
	return (1);
}

int		ft_set_environment(t_data *in)
{
	char	**args;
	t_env	*temp;
	int		ret;

	temp = in->env;
	if (in->arg == NULL)
	{
		ft_fprintf(2, "setenv: Usage: setenv ");
		ft_fprintf(2, "char *NAME, char *VALUE, int OVERWRITE\n");
		return (1);
	}
	if (!(args = ft_strsplit(in->arg, ' ')))
		return (ft_malloc_error());
	while (temp && ft_strcmp(temp->name, args[0]) != 0)
		temp = temp->next;
	if (temp)
		ret = ft_change_existent_env(temp, args);
	else
		ret = ft_add_env_to_list(in, args);
	ft_delete_two_dimens_arr(&args);
	return (ret);
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
		prev = temp;
		temp = temp->next;
	}
	ft_delete_two_dimens_arr(&args);
	return (1);
}
