/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 17:52:55 by geliz             #+#    #+#             */
/*   Updated: 2020/02/28 22:30:52 by geliz            ###   ########.fr       */
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
