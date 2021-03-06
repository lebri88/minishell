# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: geliz <geliz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/18 12:46:02 by geliz             #+#    #+#              #
#    Updated: 2020/03/01 16:37:28 by geliz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror
HEADERS = ./includes
SRC_DIR = ./src
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/ft_readstring.c $(SRC_DIR)/ft_create_and_delete_t_data.c \
	$(SRC_DIR)/ft_execute_command.c $(SRC_DIR)/ft_print_error.c $(SRC_DIR)/ft_check_and_exec_builtins.c \
	$(SRC_DIR)/ft_change_dir_cmd.c $(SRC_DIR)/ft_environment_list.c $(SRC_DIR)/ft_change_dir_variants.c \
	$(SRC_DIR)/ft_print_or_change_env_values.c $(SRC_DIR)/ft_find_command_in_way_or_cur_dir.c \
	$(SRC_DIR)/ft_check_and_set_home_pwd_env.c $(SRC_DIR)/ft_unset_environment.c $(SRC_DIR)/ft_change_env_variables_in_arg.c
OBJ_DIR = ./obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIB_DIR = ./libft
all: $(NAME)

.PHONY: clean fclean re

$(NAME): LIB $(OBJ)
		@gcc $(FLAGS) $(OBJ) -I$(HEADERS) -L$(LIB_DIR) -lft -o $(NAME)
		@echo "[\x1b[37;42;1m$(NAME) COMPILED\x1b[0m]"

LIB:
		@make -C $(LIB_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(@D)
		@gcc -c $(FLAGS) -I$(HEADERS) $< -o $@

clean:
		@make clean -C $(LIB_DIR)
		@rm -rf $(OBJ_DIR)
		@echo "[\x1b[37;41;1m$(NAME) OBJECTS DELETED\x1b[0m]"

fclean: clean
		@make fclean -C $(LIB_DIR)
		@rm -f $(NAME)
		@rm -rf $(OBJ_DIR)
		@echo "[\x1b[37;41;1m$(NAME) DELETED\x1b[0m]"

re: fclean all
