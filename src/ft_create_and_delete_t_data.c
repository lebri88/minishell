/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_and_delete_t_data.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 17:11:08 by geliz             #+#    #+#             */
/*   Updated: 2020/02/28 18:43:35 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_two_dimens_arr(char ***arr)
{
	int		i;
	char	**temp;

	if (***arr && **arr)
	{
		temp = *arr;
		i = 0;
		while (temp[i] != NULL)
		{
			ft_strdel(&temp[i]);
			i++;
		}
		free(*arr);
		*arr = NULL;
	}
}

void	ft_delete_t_data(t_data *in)
{
	if (in)
	{
		ft_strdel(&in->cmd);
		ft_strdel(&in->arg);
		ft_strdel(&in->path);
		ft_delete_two_dimens_arr(&in->env_path);
		ft_strdel(&in->curdir);
		ft_remove_env_list(in->env);
		free(in);
	}
	in = NULL;
}

char	*ft_get_current_dir(void)
{
	char	*ret;
	int		i;

	i = 1;
	ret = NULL;
	while (ret == NULL)
	{
		ret = getcwd(NULL, 1024 * i);
		i++;
	}
	return (ret);
}

char	**ft_get_path_from_environ(t_env *env)
{
	char	**ret;

	while (ft_strcmp(env->name, "PATH") != 0)
		env = env->next;
	ret = NULL;
	if (env)
		ret = ft_strsplit(env->value, ':');
	return (ret);
}

t_data	*ft_create_t_data(char **env, t_data *in)
{
	t_data	*new;

	if (in != NULL)
	{
		ft_strdel(&in->cmd);
		ft_strdel(&in->path);
		ft_strdel(&in->arg);
		ft_delete_two_dimens_arr(&in->env_path);
		in->env_path = ft_get_path_from_environ(in->env);
		ft_strdel(&in->curdir);
		in->curdir = ft_get_current_dir();
		return (in);
	}
	if (!(new = malloc(sizeof(t_data))))
		return (NULL);
	new->cmd = NULL;
	new->path = NULL;
	new->arg = NULL;
	new->env = ft_env_to_list(env);
	new->env_path = ft_get_path_from_environ(new->env);
	new->curdir = ft_get_current_dir();
	return (new);
}
