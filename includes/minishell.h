/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 13:55:12 by geliz             #+#    #+#             */
/*   Updated: 2020/02/28 22:15:10 by geliz            ###   ########.fr       */
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

typedef struct		s_env
{
    char			*name;
    char			*value;
    struct s_env	*next;
}					t_env;

typedef struct		s_data
{
    char            *cmd;
    char            *arg;
    char            *path;
    char            **env_path;
    char            *curdir;
    t_env           *env;
}                   t_data;

int		main(int argn, char **argv, char **environ);

int     ft_readstring(char **environ, t_data **in);
int		ft_parcing_comamnds(char *str, t_data *in);
char	*ft_skip_whitespaces(char *str);
char	*ft_parcing_cmd(char *str, t_data *in);

t_data	*ft_create_t_data(char **env, t_data *in);
char	*ft_get_current_dir(void);
char	**ft_get_path_from_environ(t_env *env);
void	ft_delete_t_data(t_data *in);
void	ft_delete_two_dimens_arr(char ***arr);

int		ft_execute_command_hub(t_data *in, char **env);

void	ft_print_error(int err, t_data *in);

int		ft_check_and_exec_builtins(t_data *in);

int		ft_change_directory_cmd(t_data *in);

int		ft_change_to_home_directory(t_data *in);
int		ft_change_dir_to_old_pwd(t_data *in);
int		ft_change_dir_from_root(t_data *in, char *arg);
int		ft_change_dir_from_cur_dir(char *arg, t_data *in);
void	ft_print_cd_error(char *path);

t_env	*ft_env_to_list(char **env);
void	ft_remove_env_list(t_env *list);

int		ft_print_all_of_env_values(t_data *in);

int		ft_find_command_in_way_or_cur_dir(t_data *in, char **cname);

#endif