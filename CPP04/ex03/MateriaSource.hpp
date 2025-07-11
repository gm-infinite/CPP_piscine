
#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP
#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource{

public:
	MateriaSource(void);
	~MateriaSource(void);
	MateriaSource(const MateriaSource& other);
	MateriaSource& operator=(const MateriaSource& other);

	void learnMateria(AMateria* amateria);
	AMateria* createMateria(std::string const & type);
	
private:
	AMateria *Memory[4];
	int mem_index;
};

#endif /* MATERIASOURCE_HPP */