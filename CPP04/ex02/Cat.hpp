
#ifndef CAT_HPP
#define CAT_HPP
#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal{

public:
	Cat(void);
	~Cat(void);
	Cat(const Cat& other);
	Cat& operator=(const Cat& other);

	void makeSound(void) const;

	const Brain* getBrain(void) const;
	void setBrainIdea(int i, const std::string& idea);
private:
	Brain *brain;
};

#endif /* CAT_HPP */