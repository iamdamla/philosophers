# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: derblang <derblang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/27 13:15:14 by derblang          #+#    #+#              #
#    Updated: 2023/08/07 09:35:54 by derblang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = srcs/main.c srcs/utils.c srcs/check_args.c srcs/routine.c srcs/time.c srcs/death.c

OBJS = 	${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(FLAGS) $(OBJS)  -o $(NAME) 

debug: $(OBJS)
		$(CC) $(CFLAGS)  -fsanitize=thread $(OBJS) -o $(NAME)


clean:
	$(RM) $(OBJS)

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re