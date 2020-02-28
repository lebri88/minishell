/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:17:02 by geliz             #+#    #+#             */
/*   Updated: 2020/02/28 18:07:32 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parcing_cmd(char *str, t_data *in)
{
	int		i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
		i++;
	in->cmd = ft_strsub(str, 0, i);
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
	if (str[i] == '\0')
		return (NULL);
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

int		ft_readstring(char **env, t_data **info)
{
	ssize_t	i;
	char	*buf;
	char	*temp;
	t_data	*in;

	in = *info == NULL ? NULL : *info;
	if (!(buf = ft_strnew(1024)))
		return (-1);
	i = read(1, buf, 1024);
	buf[i - 1] = '\0';
	temp = ft_skip_whitespaces(buf);
	if (ft_strnstr(temp, "exit", 4))
	{
		ft_strdel(&buf);
		temp = NULL;
		return (1);
	}
//	if (in == NULL)
//		ft_printf("\nALARM\n");
	if (!(in = ft_create_t_data(env, in)))
		return (-1);
	*info = in;
	ft_parcing_commands(buf, in);
	if (in->cmd)
		ft_execute_command_hub(in, env);
	ft_fprintf(2, "MSHELL$>");
	ft_strdel(&buf);
	return (0);
}
