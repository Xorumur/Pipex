# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 06:24:56 by mlecherb          #+#    #+#              #
#    Updated: 2022/03/30 16:25:51 by mlecherb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

OBJ			= $(SRCS:.c=.o)

CFLAGS		= -Wall -Wextra -Werror

SRCS =		srcs/pipex.c srcs/parsing_data.c srcs/utils.c lib/ft_split.c \
			lib/ft_strdup.c lib/ft_strjoin.c lib/ft_strlen.c lib/ft_strncmp.c \

$(NAME):	$(OBJ)
			gcc $(FLAGS) $(OBJ) -o $(NAME)

all:		$(NAME)

clean:
			rm -f $(OBJ)

fclean: 	clean
			rm -f $(NAME)

norme:
			norminette $(SRCS)

re:			fclean all

.PHONY :	all clean fclean re