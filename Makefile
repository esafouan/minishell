# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 23:58:24 by kremidi           #+#    #+#              #
#    Updated: 2023/03/27 21:32:49 by kremidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC =	first_split.c\
		parser.c\
		ft_substr.c\
		utils/ft_atoi_fd.c \
		utils/ft_free.c \
		utils/ft_lstnew.c \
		utils/ft_get_next_line.c\
		utils/ft_lstadd_back.c \
		utils/ft_lstadd_front.c \
		utils/ft_putchar_fd.c \
		utils/ft_putendl.c \
		utils/ft_putstr_fd.c \
		utils/ft_strchr_fd.c \
		utils/ft_strcmp.c \
		utils/ft_strlcpy.c \
		utils/ft_strlen.c \
		utils/ft_strncmp.c \
		builtin/ft_builtins_utils.c \
		builtin/ft_builtins_utils2.c \
		builtin/ft_builtins_utils3.c \
		builtin/ft_builtins_utils4.c \
		builtin/ft_builtins_utils5.c \
		builtin/ft_builtins_utils6.c \
		builtin/ft_builtins_utils7.c \
		builtin/ft_cd.c \
		builtin/ft_cd_utils.c \
		builtin/ft_echo.c \
		builtin/ft_env.c \
		builtin/ft_exit.c \
		builtin/ft_export.c \
		builtin/ft_export2.c \
		builtin/ft_export3.c \
		builtin/ft_perror.c \
		builtin/ft_pwd.c \
		builtin/ft_unset.c \
		builtin/ft_heredoc.c \
		builtin/ft_heredoc_exp.c \
		builtin/ft_heredoc_exp2.c \
		builtin/ft_builtins.exec.c \
		ft_strjoin.c \
		ft_itoa.c \
		ft_strdup.c \
		builtin/ft_path.c\
		builtin/ft_path1.c\
		redirection/redirection.c\
		redirection/redirection2.c\
		redirection/redirection3.c\
		redirection/redirection4.c\
		ft_strlcpy.c \
		get_envirement.c \
		linkedlist.c \
		get_command.c \
		syntax_error.c \
		fill_variables.c \
		ft_strtrim.c \
		builtin/ft_heredoc_utils.c\
		final_output.c\
		get_envirement_quotes.c\
		lasttrim.c\
		new_input.c\
		skiper.c\
		syntax_error_helper.c\
		envirement_helper.c\
		quote.c\
		quote_helper.c\
		utils.c\

OBJ = ${SRC:.c=.o}
CFLAGS = -Wall -Wextra -Werror
CC = cc

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC)  $(OBJ)  -lreadline  -lreadline -L/Users/kremidi/goinfre/homebrew/opt/readline/lib -I/Users/kremidi/goinfre/homebrew/opt/readline/include -o $(NAME) 
clean:
	rm -rf $(OBJ)
fclean:
	rm -rf $(OBJ) $(NAME)
re: fclean all