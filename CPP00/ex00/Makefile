# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 11:20:24 by kuzyilma          #+#    #+#              #
#    Updated: 2025/06/02 16:04:27 by kuzyilma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPPFILES = megaphone.cpp

CPPFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = megaphone

all: $(NAME)

$(NAME):
	c++ $(CPPFLAGS) $(CPPFILES) -o $(NAME)

clean:
	rm -f $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re