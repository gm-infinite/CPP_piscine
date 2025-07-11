
#ifndef CURE_HPP
#define CURE_HPP
#include "AMateria.hpp"
#include "Character.hpp"
#include <iostream>

class Cure : public AMateria{

public:
	Cure(void);
	~Cure(void);
	Cure(const Cure& other);
	Cure& operator=(const Cure& other);

	AMateria* clone() const;
	void use(ICharacter& target);

private:

};

#endif /* CURE_HPP */
