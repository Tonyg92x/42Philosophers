# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguay <aguay@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/31 08:51:26 by mmondell          #+#    #+#              #
#    Updated: 2022/04/14 08:42:50 by aguay            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#*#######################################################
##*          ERASE COMMENTS FOR BONUS PARTS            ##
#*#######################################################

## -----  NAME OF THE PROGRAMM ----- ##
NAME 			= philo

## ----- CHOOSE COMPILER AND FLAGS ----- ##
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -pthread -g

## ----- PATH TO FOLDERS ----- ##
SRCS_DIR		= srcs/

OBJ_DIR			= obj/

INCLUDE_DIR		= includes/

## ----- SOURCE FILES ----- ##
SRCS_FILES		=						\
			main.c						\
			initialise_philos.c			\
			args_validation.c			\
			ft_atoi.c					\
			ft_atol.c					\
			ft_isdigit.c				\
			philo_utils.c				\
			philo_utils2.c				\

## ----- .C TO .O CONVERT ----- ##
OBJ_FILES		= $(SRCS_FILES:.c=.o)

## ----- ADDPREFIX TO FILES ----- ##
SRCS			= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS			= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
VPATH			= $(SRCS_DIR) 

#--------------------------------------------------------------#

## ----- TOOLS AND COLORS ----- ##
RM			= rm -Rf
NO_PRINT		= --no-print-directory
RED 			= \033[31m
GREEN 			= \033[32m
YELLOW 			= \033[33m
BLUE 			= \033[34m
PINK 			= \033[35m
AQUA 			= \033[36m
GREY 			= \033[37m
UNDERLINE 		= \033[4m
NORMAL 			= \033[0m

## ----- ALL ACTION DEPENDENCIES AND RECIPE FOR MAIN PROGRAM ----- ##
all: obj $(NAME)

$(OBJ_DIR)%.o:%.c
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(OBJ_DIR)* $(CFLAGS) -o $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

## ----- CLEAN COMMANDS ----- ##
clean:
	$(RM) $(OBJS)
	rm -rf obj

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
