CPP_FILES = main.cpp Bureaucrat.cpp
FLAGS = -std=c++98 -Wall -Wextra -Werror
NAME = test
all: $(NAME)

$(NAME):
	c++ $(FLAGS) $(CPP_FILES) -o $(NAME)

clean:
	rm -f $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all

main: re
	clear
	

.PHONY: all clean fclean re