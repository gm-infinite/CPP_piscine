
#ifndef ICE_HPP
#define ICE_HPP
#include "AMateria.hpp"
#include "Character.hpp"
#include <iostream>

class Ice : public AMateria{

public:
	Ice(void);
	~Ice(void);
	Ice(const Ice& other);
	Ice& operator=(const Ice& other);

	AMateria* clone() const;
	void use(ICharacter& target);
	
private:

};

#endif /* ICE_HPP */