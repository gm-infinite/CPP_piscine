
#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "ICharacter.hpp"

class Character : ICharacter{

public:
	Character(void);
	~Character(void);
	Character(const Character& other);
	Character& operator=(const Character& other);

private:

};

#endif /* CHARACTER_HPP */