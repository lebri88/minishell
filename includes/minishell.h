/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 13:55:12 by geliz             #+#    #+#             */
/*   Updated: 2020/02/21 18:42:33 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "ft_printf.h"
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <sys/types.h>

typedef struct		s_data
{
    char            *cmd;
    char            *arg;
    char            *path;
    char            **env_path;
}                   t_data;

int		main(int argn, char **argv, char **environ);
t_data	*ft_create_t_data(char **env);

int     ft_readstring(t_data *in, char **environ);
int		ft_parcing_comamnds(char *str, t_data *in);
char	*ft_skip_whitespaces(char *str);
char	*ft_parcing_cmd(char *str, t_data *in);


int		ft_execute_command_hub(t_data *in, char **env);

#endif