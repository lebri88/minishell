/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:17:02 by geliz             #+#    #+#             */
/*   Updated: 2020/03/01 18:50:17 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_print_promt_and_return_null(void)
{
	ft_fprintf(2, "MSHELL$>");
	return (NULL);
}

int		ft_parcing_cmd(char *str, t_data *in)
{
	int		i;

	i = 0;
	str = ft_skip_whitespaces(str);
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

char	*ft_readstring(t_data *in, char **env)
{
	ssize_t	i;
	char	*buf;
	char	*whtsp;

	i = 0;
	if (!(buf = ft_strnew(1024)))
		return (NULL);
	i = read(1, buf, 1024);
	if (i == 1 && buf[i] == '\0')
		return (ft_print_promt_and_return_null());
	buf[i - 1] = '\0';
	if (ft_strchr(buf, '$') != NULL)
	{
		if (!(buf = ft_change_env_variables_in_arg(env, buf, in)))
			return (ft_print_promt_and_return_null());
	}
	if (!(whtsp = ft_skip_whitespaces(buf)))
		return (ft_print_promt_and_return_null());
	return (buf);
}

int		ft_minishell_hub(char **env, t_data **info)
{
	char	*buf;
	char	*temp;
	t_data	*in;

	in = *info == NULL ? NULL : *info;
	if (!(buf = ft_readstring(in, env)))
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
