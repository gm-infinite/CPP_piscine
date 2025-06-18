CPP_FILES = main.cpp ClapTrap.cpp ScavTrap.cpp FragTrap.cpp DiamondTrap.cpp
FLAGS = -std=c++98 -Wall -Wextra -Werror
NAME = diamondtraptest
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
	

.PHONY = all clean fclean re