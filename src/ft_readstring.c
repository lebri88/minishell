/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:17:02 by geliz             #+#    #+#             */
/*   Updated: 2020/02/29 20:36:06 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_parcing_cmd(char *str, t_data *in)
{
	int		i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
		i++;
	if (!(in->cmd = ft_strsub(str, 0, i)))
		return (-1);
	str = ft_skip_whitespaces(&str[i]);
	if (!(in->arg = ft_strdup(str)))
		return (-1);
	return (1);
}

char	*ft_skip_whitespaces(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '\0')
		return (NULL);
	return (&str[i]);
}

char	*ft_readstring(void)
{
	ssize_t	i;
	char	*buf;

	i = 0;
	if (!(buf = ft_strnew(1024)))
		return (NULL);
	i = read(1, buf, 1024);
	if (i == 1 && buf[i] == '\0')
	{
		ft_fprintf(2, "MSHELL$>");
		return (NULL);
	}
	buf[i - 1] = '\0';
	return (buf);
}

int		ft_minishell_hub(char **env, t_data **info)
{
	char	*buf;
	char	*temp;
	t_data	*in;

	in = *info == NULL ? NULL : *info;
	if (!(buf = ft_readstring()))
		return (0);
	temp = ft_skip_whitespaces(buf);
	if (ft_strnstr(temp, "exit", 4))
	{
		ft_strdel(&buf);
		temp = NULL;
		return (1);
	}
	if (!(in = ft_create_t_data(env, in)))
		return (-1);
	*info = in;
	ft_parcing_cmd(temp, in);
	if (in->cmd)
		ft_execute_command_hub(in);
	ft_fprintf(2, "MSHELL$>");
	ft_strdel(&buf);
	return (0);
}
