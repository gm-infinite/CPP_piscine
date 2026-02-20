CPP_FILES = main.cpp  Zombie.cpp zombieHorde.cpp
FLAGS = -std=c++98 -Wall -Wextra -Werror
NAME = zombieHorde
all: $(NAME)

$(NAME):
	c++ $(FLAGS) $(CPP_FILES) -o $(NAME)

clean:
	rm $(NAME)

fclean:
	rm $(NAME)

re: fclean all

main: re
	clear
	

.PHONY: all clean fclean re