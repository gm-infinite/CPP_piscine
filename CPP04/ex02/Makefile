CPP_FILES = main.cpp Cat.cpp Animal.cpp Dog.cpp WrongAnimal.cpp WrongCat.cpp Brain.cpp
FLAGS = -std=c++98 -Wall -Wextra -Werror
NAME = animaltest
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