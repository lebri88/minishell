/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 17:52:55 by geliz             #+#    #+#             */
/*   Updated: 2020/02/29 19:19:40 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error(int err, t_data *in)
{
	if (err == -1)
		ft_fprintf(2, "MSHELL: %s: command not found\n", in->cmd);
	if (err == -2)
		ft_fprintf(2, "MSHELL: %s: Permission denied\n", in->cmd);
	/*
	**if you try to execute "/" original shell tells "ACCESS DENIED" =__=
	*/
}

int		ft_malloc_error(void)
{
	ft_fprintf(2, "Cannot allocate memory.");
	return (1);
}
