/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 13:55:12 by geliz             #+#    #+#             */
/*   Updated: 2020/03/01 18:50:57 by geliz            ###   ########.fr       */
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
    char            *curdir;
    t_env           *env;
}                   t_data;
/*
** main.c
*/
int		main(int argn, char **argv, char **environ);
/*
**ft_readstring.c
*/
int		ft_minishell_hub(char **env, t_data **info);
char	*ft_readstring(t_data *in, char **env);
char	*ft_skip_whitespaces(char *str);
int     ft_parcing_cmd(char *str, t_data *in);
/*
**ft_create_and_delete_t_data.c
*/
t_data	*ft_create_t_data(char **env, t_data *in);
char	*ft_get_current_dir(void);
char	**ft_get_path_from_environ(t_env *env);
void	ft_delete_t_data(t_data *in);
void	ft_delete_two_dimens_arr(char ***arr);
/*
**ft_execute_command.c
*/
int		ft_execute_command_hub(t_data *in);
int		ft_execute_command(t_data *in, char *cname);
char	**ft_create_args_list(t_data *in);
char	*ft_find_command_in_path_dirs(t_data *in);
char	*ft_open_dir_and_find_command(char *openit, t_data *in);
/*
**ft_print_error.c
*/
void	ft_print_error(int err, t_data *in);
int		ft_malloc_error(void);
/*
**ft_check_and_exec_builtins.c
*/
int		ft_check_and_exec_builtins(t_data *in);
int		ft_check_echo_cmd(t_data *in);
int		ft_check_cd_cmd(t_data *in);
int		ft_check_env_group_cmd(t_data *in);
/*
**ft_change_dir_cmd.c
*/
int		ft_change_directory_cmd(t_data *in);
int		ft_get_first_arg(char *str, char **arg, t_data *in);
int		ft_change_old_pwd_in_env(t_data *in);
int		ft_add_oldpwd_to_env(t_data *in);
/*
**ft_change_dir_variants.c
*/
int		ft_change_to_home_directory(t_data *in);
int		ft_change_dir_to_old_pwd(t_data *in);
int		ft_change_dir_from_root(t_data *in, char *arg);
int		ft_change_dir_from_cur_dir(char *arg, t_data *in);
void	ft_print_cd_error(char *path);
/*
**ft_environment_list.c
*/
t_env	*ft_env_to_list(char **env);
void	ft_remove_env_list(t_env *list);
char	**ft_take_env_from_struct(t_data *in);
t_env	*ft_create_next_t_env_list(char *env, t_env *prev);
/*
**ft_print_or_change_env_values.c
*/
int		ft_set_environment(t_data *in);
int		ft_change_existent_env(t_env *temp, char **args);
int		ft_add_env_to_list(t_data *in, char **args);
int		ft_print_all_of_env_values(t_data *in);
/*
**ft_find_command_in_way_or_cur_dir.c
*/
int		ft_find_command_in_way_or_cur_dir(t_data *in, char **cname);
void	ft_close_dir_and_free_str(DIR *dir, char *fname, char *fpath);
int		ft_get_path_and_name(t_data *in, char **name, char **path);
/*
**ft_check_and_set_home_pwd_env.c
*/
int		ft_check_and_set_home_pwd_env(t_data *in);
t_env	*ft_check_in_env(t_data *in, char *str);
int		ft_add_pwd_to_env(t_data *in, t_env *last);
/*
**ft_unset_environment.c
*/
int		ft_unset_environment(t_data *in);
void	ft_delete_env_and_set_next(t_data *in, t_env *temp, t_env *prev);
/*
**ft_change_env_variables_in_arg.c
*/
char	*ft_change_env_variables_in_arg(char **env, char *str, t_data *in);
int		ft_find_change_in_env(char **arg, char **env);
int		ft_find_change_in_filled_env(char **arg, t_data *in);
char	*ft_build_changed_arg(int i, char **temp);
void	ft_delete_array(char ***arr, int i);

#endif