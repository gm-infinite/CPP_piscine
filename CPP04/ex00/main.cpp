
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    {
    const Animal* meta = new Animal();
    const Dog* j = new Dog();
    const Cat* i = new Cat();

    std::cout << std::endl;

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;

    std::cout << std::endl;

    i->makeSound(); //will output the cat sound!
    j->makeSound();
    meta->makeSound();

    std::cout << std::endl;
    
    delete meta;
    delete j;
    delete i;
    }
    std::cout << std::endl;
    {
    const WrongAnimal* meta = new WrongAnimal();
    const Dog* j = new Dog();
    const WrongCat* i = new WrongCat();

    std::cout << std::endl;

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;

    std::cout << std::endl;

    i->makeSound(); //will output the cat sound!
    j->makeSound();
    meta->makeSound();

    std::cout << std::endl;

    delete meta;
    delete j;
    delete i;
    }
}