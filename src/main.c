/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 13:54:36 by geliz             #+#    #+#             */
/*   Updated: 2020/02/21 17:36:43 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (new);
}

int		main(int argn, char **argv, char **environ)
{
	int		exit;
	t_data	*in;
	
	if (argn > 1)
		return (-1);
	(void)argv;
	exit = 0;
	if (!(in = ft_create_t_data(environ)))
		return (-1);
	ft_printf("MSHELL$>");
	while (exit != 1)
		exit = ft_readstring(in, environ);
	return (0);
}
