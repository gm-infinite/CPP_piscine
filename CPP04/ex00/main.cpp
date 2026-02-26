#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    std::cout << "\n========== EX00: POLYMORPHISM ==========\n" << std::endl;

    // TEST 1: Subject's required test
    std::cout << "--- TEST 1: Subject's required test ---\n" << std::endl;
    {
        const Animal* meta = new Animal();
        const Animal* j = new Dog();
        const Animal* i = new Cat();

        std::cout << "\nj->getType(): " << j->getType() << std::endl;
        std::cout << "i->getType(): " << i->getType() << std::endl;

        std::cout << "\ni->makeSound(): "; i->makeSound();
        std::cout << "j->makeSound(): "; j->makeSound();
        std::cout << "meta->makeSound(): "; meta->makeSound();

        std::cout << "\nDeleting:" << std::endl;
        delete meta;
        delete j;
        delete i;
    }

    // TEST 2: WrongAnimal - No virtual
    std::cout << "\n--- TEST 2: WrongAnimal (no virtual) ---\n" << std::endl;
    {
        const WrongAnimal* wrongMeta = new WrongAnimal();
        const WrongAnimal* wrongCat = new WrongCat();

        std::cout << "\nwrongMeta->getType(): " << wrongMeta->getType() << std::endl;
        std::cout << "wrongCat->getType(): " << wrongCat->getType() << std::endl;

        std::cout << "\nwrongMeta->makeSound(): "; wrongMeta->makeSound();
        std::cout << "wrongCat->makeSound(): "; wrongCat->makeSound();

        std::cout << "\nDeleting:" << std::endl;
        delete wrongMeta;
        delete wrongCat;
    }

    // TEST 3: Same WrongCat object - direct call vs pointer call
    std::cout << "\n--- TEST 3: Direct call vs pointer call ---\n" << std::endl;
    {
        WrongCat wrongCatObj;

        std::cout << "\nDirect: wrongCatObj.makeSound(): "; wrongCatObj.makeSound();

        const WrongAnimal* ptr = &wrongCatObj;
        std::cout << "Pointer: ptr->makeSound(): "; ptr->makeSound();
    }

    // TEST 4: Contrast with Animal/Cat (with virtual)
    std::cout << "\n--- TEST 4: Animal/Cat with virtual ---\n" << std::endl;
    {
        Cat catObj;

        std::cout << "\nDirect: catObj.makeSound(): "; catObj.makeSound();

        const Animal* ptr = &catObj;
        std::cout << "Pointer: ptr->makeSound(): "; ptr->makeSound();
    }

    // TEST 5: Virtual destructor - deletion through base pointer
    std::cout << "\n--- TEST 5: Destructor order ---\n" << std::endl;
    {
        std::cout << "Creating Dog through Animal*:" << std::endl;
        const Animal* dogPtr = new Dog();
        std::cout << "\nDeleting through Animal*:" << std::endl;
        delete dogPtr;
    }

    // TEST 6: Array of Animals
    std::cout << "\n--- TEST 6: Array of Animals ---\n" << std::endl;
    {
        const Animal* zoo[4];
        zoo[0] = new Dog();
        zoo[1] = new Cat();
        zoo[2] = new Dog();
        zoo[3] = new Cat();

        std::cout << "\nCalling makeSound() on each:" << std::endl;
        for (int i = 0; i < 4; i++)
        {
            std::cout << "zoo[" << i << "] (" << zoo[i]->getType() << "): ";
            zoo[i]->makeSound();
        }

        std::cout << "\nDeleting all:" << std::endl;
        for (int i = 0; i < 4; i++)
            delete zoo[i];
    }

    std::cout << "\n========== END EX00 ==========\n" << std::endl;
    return 0;
}
