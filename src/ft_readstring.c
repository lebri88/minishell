/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:17:02 by geliz             #+#    #+#             */
/*   Updated: 2020/02/21 18:28:03 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parcing_cmd(char *str, t_data *in)
{
	int		i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
		i++;
	in->cmd = ft_strnew(i);
	in->cmd[i] = '\0';
	in->cmd = ft_strncpy(in->cmd, str, i);
	str = ft_skip_whitespaces(&str[i]);
	in->arg = ft_strdup(str);
	return (str);
}

/*
char	*ft_check_path(char *str, t_data *in)
{
	char	*pth;
	int		i;
}
*/

char	*ft_skip_whitespaces(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (&str[i]);
}

int		ft_parcing_commands(char *str, t_data *in)
{
	char	*temp;

	temp = ft_skip_whitespaces(str);
//	if (temp[0] == '.' || temp[0] == '/' || temp[0] == '~')
//		temp = ft_check_path(temp, in);
//	else
	temp = ft_parcing_cmd(temp, in);
//	ft_printf("%s", in->cmd);
	return (0);
}

int		ft_readstring(t_data *in, char **env)
{
	ssize_t	i;
	char	*buf;

	if (!(buf = ft_strnew(1024)))
		return (-1);
	i = read(1, buf, 1024);
	buf[i - 1] = '\0';
	if (ft_strnstr(buf, "exit", 4))
	{
		ft_strdel(&buf);
		return (1);
	}
	ft_parcing_commands(buf, in);
	if (in->cmd)
		ft_execute_command_hub(in, env);
	ft_printf("\nMSHELL$>");
	return (0);
}
