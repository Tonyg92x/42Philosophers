# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguay <aguay@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/31 08:51:26 by mmondell          #+#    #+#              #
#    Updated: 2022/03/31 07:41:24 by aguay            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#*#######################################################
##*          ERASE COMMENTS FOR BONUS PARTS            ##
#*#######################################################

## -----  NAME OF THE PROGRAMM ----- ##
NAME 			= philo

## ----- CHOOSE COMPILER AND FLAGS ----- ##
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

## ----- PATH TO FOLDERS ----- ##
SRCS_DIR		= srcs/

OBJ_DIR			= obj/

INCLUDE_DIR		= includes/

LIBFT_DIR		= libft

LIBFT_OBJ		= libft/obj/

LIBFT_INC		= libft/includes/

## ----- SOURCE FILES ----- ##
SRCS_FILES		=						\
			main.c						\

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

LIBFT			= make -C $(LIBFT_DIR)

## ----- ALL ACTION DEPENDENCIES AND RECIPE FOR MAIN PROGRAM ----- ##
all: obj $(NAME)

$(OBJ_DIR)%.o:%.c
	$(CC) $(CFLAGS) -I $(LIBFT_OBJ) -I $(INCLUDE_DIR) -I $(LIBFT_INC) -o $@ -c $<

$(NAME): $(OBJS)
	$(LIBFT)
	$(CC) $(OBJS) libft/libft.a -o $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

## ----- CLEAN COMMANDS ----- ##
clean:
	$(RM) $(OBJS) $(B_OBJS)
	@make -C $(LIBFT_DIR) clean
	rm -rf obj

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
