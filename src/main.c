/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 13:54:36 by geliz             #+#    #+#             */
/*   Updated: 2020/02/23 21:22:15 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argn, char **argv, char **environ)
{
	int		exit;

	if (argn > 1)
		return (-1);
	(void)argv;
	exit = 0;
	ft_fprintf(2, "MSHELL$>");
	while (exit != 1)
		exit = ft_readstring(environ);
	return (0);
}
