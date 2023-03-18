# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 08:50:48 by mtaib             #+#    #+#              #
#    Updated: 2023/03/14 15:51:55 by mtaib            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = pipex.c pipex_utils.c ft_split.c ft_split2.c ft_strlcpy.c pipex_utils2.c

OSRC = $(SRC:.c=.o)

NAME = pipex
CFLAGS = -Wextra -Werror -Wall 

%.o:%.c
	cc -c $(CFLAGS) $<

all: $(NAME)

$(NAME) :$(OCMN) $(OSRC)
		cc $(CFLAGS) $^ -o $(NAME)

clean :
	@rm -f *.o
fclean :
	@rm -f *.o $(NAME) $(BONUS)
re : fclean all

.PHONY : all clean fclean re bonus
