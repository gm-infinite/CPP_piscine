CPP_FILES = main.cpp Bureaucrat.cpp AForm.cpp ShrubberyCreationForm.cpp RobotomyRequestForm.cpp PresidentialPardonForm.cpp
FLAGS = -std=c++98 -Wall -Wextra -Werror
NAME = test
all: $(NAME)

$(NAME):
	c++ $(FLAGS) $(CPP_FILES) -o $(NAME)

clean:
	rm -f $(NAME)
	rm -f *_shrubbery

fclean: clean

re: fclean all

run: re
	clear
	./$(NAME)

.PHONY: all clean fclean re run