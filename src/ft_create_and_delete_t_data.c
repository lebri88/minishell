/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_and_delete_t_data.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 17:11:08 by geliz             #+#    #+#             */
/*   Updated: 2020/02/23 22:03:02 by geliz            ###   ########.fr       */
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
	ft_strdel(&in->cmd);
	ft_strdel(&in->arg);
	ft_strdel(&in->path);
	ft_delete_two_dimens_arr(&in->env_path);
	if (in)
		free(in);
	ft_strdel(&in->curdir);
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

char	**ft_get_path_from_environ(char **env)
{
	int		i;
	char	**ret;

	i = 0;
	while (ft_strstr(env[i], "PATH=") == NULL)
		i++;
	ret = ft_strsplit(&env[i][5], ':');
	return (ret);
}

t_data	*ft_create_t_data(char **env)
{
	t_data	*new;

	if (!(new = malloc(sizeof(t_data))))
		return (NULL);
	new->cmd = NULL;
	new->path = NULL;
	new->arg = NULL;
	new->env_path = ft_get_path_from_environ(env);
	new->curdir = ft_get_current_dir();
	return (new);
}
