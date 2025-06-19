
#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP
#include <string>
#include <iostream>

class WrongAnimal {

public:
	WrongAnimal(void);
	WrongAnimal(const std::string& type);
	~WrongAnimal(void);
	WrongAnimal(const WrongAnimal& other);
	WrongAnimal& operator=(const WrongAnimal& other);

	void makeSound(void) const;
	
	const std::string& getType(void) const;
	void setType(const std::string& type);

protected:
	std::string type;

};

#endif /* WRONGANIMAL_HPP */
