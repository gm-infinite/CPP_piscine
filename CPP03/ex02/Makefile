CPP_FILES = main.cpp ClapTrap.cpp ScavTrap.cpp FragTrap.cpp
FLAGS = -std=c++98 -Wall -Wextra -Werror
NAME = fragtraptest
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