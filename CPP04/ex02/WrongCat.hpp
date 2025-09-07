
#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP
#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal{

public:
	WrongCat(void);
	~WrongCat(void);
	WrongCat(const WrongCat& other);
	WrongCat& operator=(const WrongCat& other);

	void makeSound(void) const;
	
private:

};

#endif /* WRONGCAT_HPP */

