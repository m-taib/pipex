# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 08:50:48 by mtaib             #+#    #+#              #
#    Updated: 2023/05/16 13:18:37 by mtaib            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = mand.c pipex_utils.c ft_split2.c ft_strlcpy.c pipex_utils2.c pipex_utils3.c exec_cmds.c pipex_utils4.c pipex_utils5.c
BSRC = bonus.c pipex_utils.c ft_split2.c ft_strlcpy.c pipex_utils2.c pipex_utils3.c exec_cmds.c pipex_utils4.c pipex_utils5.c
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
