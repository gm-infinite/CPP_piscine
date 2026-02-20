
CPP_FILES = Account.cpp tests.cpp
FLAGS = -std=c++98 -Wall -Wextra -Werror
NAME = test

all: $(NAME)

$(NAME):
	c++ $(FLAGS) $(CPP_FILES) -o $(NAME)

clean:

fclean:
	rm $(NAME)

re: fclean all

main: re
	clear
	

.PHONY: all clean fclean re