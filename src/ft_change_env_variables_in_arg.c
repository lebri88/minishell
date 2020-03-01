/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_env_variables_in_arg.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:24:58 by geliz             #+#    #+#             */
/*   Updated: 2020/03/01 19:01:28 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_array_and_string(char ***arr, int i, char *str)
{
	char	**temp;
	int		j;

	ft_strdel(&str);
	temp = *arr;
	j = 0;
	while (j < i)
	{
		ft_strdel(&temp[j]);
		j++;
	}
	free(temp);
	*arr = NULL;
	temp = NULL;
}

int		ft_find_change_in_env(char **arg, char **env)
{
	char	*str;
	int		env_len;
	int		i;

	i = 0;
	env_len = 0;
	str = *arg;
	while (env[i])
	{
		while (env[i][env_len] != '=')
			env_len++;
		if (ft_strncmp(&str[1], env[i], env_len) == 0)
		{
			if (!(str = ft_strdup(&env[i][env_len + 1])))
				return (-1);
			ft_strdel(arg);
			*arg = str;
			return (1);
		}
		env_len = 0;
		i++;
	}
	if (!env[i])
		ft_strdel(arg);
	return (1);
}

int		ft_find_change_in_filled_env(char **arg, t_data *in)
{
	t_env	*temp;
	char	*str;

	temp = in->env;
	str = *arg;
	while (temp)
	{
		if (ft_strcmp(&str[1], temp->name) == 0)
		{
			if (!(str = ft_strdup(temp->value)))
				return (-1);
			ft_strdel(arg);
			*arg = str;
			return (1);
		}
		temp = temp->next;
	}
	if (!temp)
		ft_strdel(arg);
	return (1);
}

char	*ft_build_changed_arg(int i, char **temp)
{
	int		j;
	char	*ret;

	j = 0;
	ret = NULL;
	while (j < i)
	{
		if (!ret && temp[j])
		{
			if (!(ret = ft_strjoin_arg("%s %s", temp[j], " ")))
				return (NULL);
		}
		else if (ret && temp[j])
		{
			if (!(ret = ft_strjoin_arg("%f %s %s", ret, " ", temp[j])))
				return (NULL);
		}
		j++;
	}
	return (ret);
}

char	*ft_change_env_variables_in_arg(char **env, char *str, t_data *in)
{
	char	*ret;
	char	**temp;
	int		i;

	i = 0;
	if (!(temp = ft_strsplit(str, ' ')))
		return (NULL);
	while (temp[i])
	{
		if (ft_strchr(temp[i], '$'))
		{
			if (in && ft_find_change_in_filled_env(&temp[i], in) == -1)
				return (NULL);
			else if (!in && ft_find_change_in_env(&temp[i], env) == -1)
				return (NULL);
		}
		i++;
	}
	if (!(ret = ft_build_changed_arg(i, temp)))
	{
		ft_delete_array_and_string(&temp, i, str);
		return (NULL);
	}
	ft_delete_array_and_string(&temp, i, str);
	return (ret);
}
