/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 13:54:36 by geliz             #+#    #+#             */
/*   Updated: 2020/02/29 20:36:54 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argn, char **argv, char **environ)
{
	int		exit;
	t_data	*in;

	if (argn > 1)
		return (-1);
	(void)argv;
	exit = 0;
	in = NULL;
	ft_fprintf(2, "MSHELL$>");
	while (exit != 1)
	{
		exit = ft_minishell_hub(environ, &in);
	}
	ft_delete_t_data(in);
	return (0);
}
