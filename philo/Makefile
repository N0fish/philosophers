# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: algultse <algultse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 16:13:30 by algultse          #+#    #+#              #
#    Updated: 2024/04/15 15:57:09 by algultse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRCDIR = ./srcs/
INCDIR = ./include/
OBJDIR = ./obj/

SRC = check.c init.c utils.c ft_malloc.c \
	philo.c philo_action.c philo_state.c \
	main.c
OBJS = $(SRC:%.c=$(OBJDIR)%.o)

all: $(NAME)

$(NAME): $(OBJS) $(MANDATORY_OBJS)
	$(CC) $(OBJS) $(MANDATORY_OBJS) -o $(NAME) -pthread

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re