# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 08:50:48 by mtaib             #+#    #+#              #
#    Updated: 2023/03/28 17:44:57 by mtaib            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = mand.c pipex_utils.c ft_split.c ft_split2.c ft_strlcpy.c pipex_utils2.c
BSRC = pipex.c pipex_utils.c ft_split.c ft_split2.c ft_strlcpy.c pipex_utils2.c
OSRC = $(SRC:.c=.o)
OBSRC = $(BSRC:.c=.o)

NAME = pipex
CFLAGS = -Wextra -Werror -Wall 
BONUS = pipex_bonus
%.o:%.c
	cc -c $(CFLAGS) $<

all: $(NAME)

$(NAME) :$(OSRC)
		cc $(CFLAGS) $^ -o $(NAME)

bonus : $(BONUS)

$(BONUS) :$(OBSRC) 
		cc $(CFLAGS) $^ -o $(BONUS)
clean :
	@rm -f *.o
fclean :
	@rm -f *.o $(NAME) $(BONUS)
re : fclean all

.PHONY : all clean fclean re bonus
