
#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include "IMateriaSource.hpp"

class ICharacter;

class AMateria
{
protected:
    std::string type;                    // "ice" or "cure"

public:
    AMateria();
    AMateria(std::string const & type);
    AMateria(const AMateria& other);
    AMateria& operator=(const AMateria& other);
    virtual ~AMateria();

    std::string const & getType() const; // Returns the type (NOT virtual)
    
    virtual AMateria* clone() const = 0;                    // PURE VIRTUAL
    virtual void use(ICharacter& target);                   // VIRTUAL (has default)
};

#endif /* AMATERIA_HPP */