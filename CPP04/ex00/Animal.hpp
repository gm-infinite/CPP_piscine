
#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <string>
#include <iostream>

class Animal {

public:
	Animal(void);
	Animal(const std::string& type);
	virtual ~Animal(void);
	Animal(const Animal& other);
	Animal& operator=(const Animal& other);

	virtual void makeSound(void) const;
	
	const std::string& getType(void) const;
	void setType(const std::string& type);

	

protected:
	std::string type;

};

#endif /* ANIMAL_HPP */

