# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 14:20:37 by ysonmez           #+#    #+#              #
#    Updated: 2021/11/11 19:26:47 by ysonmez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Reset
Set_Color		=		\033[0m						# Text Reset

# Regular Colors
Black			=		\033[0;30m					# Black
Red				=		\033[0;31m					# Red
Green			=		\033[0;32m					# Green
Yellow			=		\033[0;33m					# Yellow
Blue			=		\033[0;34m					# Blue
Purple			=		\033[0;35m					# Purple
Cyan			=		\033[0;36m					# Cyan
White			=		\033[0;37m					# White

NAME			=		minishell

SRCS			=		srcs/main.c srcs/exec_utils.c srcs/exec_route.c srcs/exec_task.c srcs/exec_main.c\
						srcs/env_create.c srcs/dollar_sign.c srcs/ft_replace.c\

OBJS			=		$(SRCS:.c=.o)

LIB				=		make -C ./ft_lib

LDFLAGS			=		"-L/Users/$(USER)/.brew/opt/readline/lib"

CPPFLAGS		=		"-I/Users/$(USER)/.brew/opt/readline/include"

CFLAGS			=		

RM				=		rm -f

$(NAME)			:		$(OBJS)
						@echo "Creating $(Red)MINISHELL$(Set_Color)"
						$(LIB)
						@gcc -lreadline $(LDFLAGS) $(CPPFLAGS) $(CFLAGS) -fsanitize=address $(OBJS) ft_lib/libft.a -o $(NAME)
						@echo "$(Red)MINISHELL: $(Set_Color)$(Green)done$(Set_Color)"

lib				:
						$(LIB)

clean			:
						$(RM) $(OBJS)

fclean			:		clean
						$(RM) $(NAME)
						cd ./libft && make fclean

all				:		$(NAME)

bonus			:		all

re				:		fclean all

.PHONY			:		clean fclean all re bonus